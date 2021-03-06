package model

import (
	"github.com/sunfmin/batchbuy/api"
	"labix.org/v2/mgo/bson"
	"time"
	// "fmt"
)

var userTN = "users"
var userCol = db.C(userTN)

type User struct {
	Id         bson.ObjectId "_id"
	Name       string
	Email      string
	AvatarLink string
}

// TODO this design seems unnecesary, and make it more troublesome to use User#Put
type UserInput api.UserInput

func (user *User) Put(email string, input UserInput) (err error) {
	count, err := userCol.Find(M{"email": email}).Count()
	if err != nil {
		return
	}

	if count == 0 {
		err = userCol.Insert(input)
	} else {
		err = userCol.Update(M{"email": input.Email}, &input)
	}
	if err != nil {
		return
	}

	err = userCol.Find(M{"email": input.Email}).One(user)

	return
}

func RemoveUser(email string) (err error) {
	err = userCol.Remove(M{"email": email})
	if err != nil {
		return
	}
	// _, err = orderCol.RemoveAll(M{"userid": email})
	// if err != nil {
	//     return
	// }

	return
}

func GetUser(email string) (user *User, err error) {
	err = userCol.Find(M{"email": email}).One(&user)

	return
}

func GetAllUsersInApi() (users []*api.User, err error) {
	modelUsers := []*User{}
	err = userCol.Find(M{}).All(&modelUsers)

	for _, modelUser := range modelUsers {
		users = append(users, modelUser.ToApi())
	}

	return
}

func (user User) OrderedProducts(date time.Time) (products []Product, err error) {
	productIds, err := user.orderedProductIds(date)
	if err != nil {
		return
	}

	err = productCol.Find(M{"_id": M{"$in": productIds}}).Sort("Name").All(&products)

	return
}

func (user User) AvaliableProducts(date time.Time) (products []Product, err error) {
	productIds, err := user.orderedProductIds(date)
	if err != nil {
		return
	}

	emptyDate, err := time.Parse("2006-01-02", "0001-01-01")
	if err != nil {
		return
	}

	err = productCol.Find(M{
		"$or": []M{
			{"validfrom": emptyDate, "validto": emptyDate},
			{"validfrom": M{"$lte": date}, "validto": emptyDate},
			{"validfrom": emptyDate, "validto": M{"$gte": date}},
			{"validfrom": M{"$lte": date}, "validto": M{"$gte": date}},
		},
		"_id": M{"$nin": productIds},
	}).Sort("name").All(&products)

	return
}

func (user User) Orders(date time.Time) (orders []Order, err error) {
	err = orderCol.Find(M{"date": getDayRangeCond(date), "userid": user.Email}).All(&orders)

	return
}

func (user User) OrdersForApi(date time.Time) (orders []*api.Order, err error) {
	modelOrders, err := user.Orders(date)
	orders = ordersToApi(modelOrders)

	return
}

func (user User) orderedProductIds(date time.Time) (productIds []bson.ObjectId, err error) {
	orders, err := user.Orders(date)
	if err != nil {
		return
	}

	for _, order := range orders {
		productIds = append(productIds, bson.ObjectIdHex(order.ProductId))
	}

	return
}

func (user User) ToApi() (apiUser *api.User) {
	apiUser = &api.User{}
	apiUser.Name = user.Name
	apiUser.Email = user.Email
	apiUser.AvatarLink = user.AvatarLink

	return
}

func UnorderedUsers(date time.Time) (apiUsers []*api.User, err error) {
	orderedEmails := []string{}
	err = orderCol.Find(M{"date": getDayRangeCond(date)}).Distinct("userid", &orderedEmails)
	if err != nil {
		return
	}

	modelUsers := []User{}
	err = userCol.Find(M{}).All(&modelUsers)
	if err != nil {
		return
	}

	for _, modelUser := range modelUsers {
		orderF := false
		for _, email := range orderedEmails {
			if modelUser.Email == email {
				orderF = true
				break
			}
		}
		if !orderF {
			apiUsers = append(apiUsers, modelUser.ToApi())
		}
	}

	return
}
