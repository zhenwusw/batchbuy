//
//  FirstViewController.m
//  BatchBuy
//
//  Created by Felix Sun on 10/14/13.
//  Copyright (c) 2013 HyperMusk. All rights reserved.
//

#import "MyOrdersController.h"
#import "ProductTableViewCell.h"
#import "Api.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "Profile.h"

@interface MyOrdersController ()

{
    
    NSArray *allProducts;
    NSArray *myOrderedProducts;
}
@end

@implementation MyOrdersController

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	// Number of sections is the number of regions.
	return 2;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) {
        return myOrderedProducts.count;
    } else {
        return allProducts.count;
    }
	return 0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
	// The header for the section is the region name -- get this from the region at the section index.
	if (section == 0) {
        return @"已下订单";
    } else {
        return @"其他点心";
    }
	return @"";
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
	static NSString *MyIdentifier = @"Cell";
    
	ProductTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:MyIdentifier];

    Product *p;
    if (indexPath.section == 0) {
        Order *o = [myOrderedProducts objectAtIndex:indexPath.row];
        p = o.Product;
        cell.orderCount.text = [NSString stringWithFormat:@"%ld", (long)[o.Count integerValue]];
        cell.orderCountValue = [o.Count integerValue];
    } else {
        p = [allProducts objectAtIndex:indexPath.row];
        cell.orderCount.text = @"";
    }
    cell.productTitle.text = p.Name;
    cell.productId = p.Id;
    [cell.imageView setImageWithURL:[NSURL URLWithString:p.PhotoLink] placeholderImage:[UIImage imageNamed:@"productEmpty.png"]];
    cell.extraInfo = self.extraInfo;
	return cell;
}

- (void)refetchData:(NSString *)date {
    self.navigationItem.title = date;
    
    if (self.extraInfo == nil) {
        self.extraInfo = [NSMutableDictionary dictionaryWithDictionary:@{@"date":date, @"email":self.profile.email}];
    } else {
        [self.extraInfo setValue:date forKey:@"date"];
    }
    
    Service *s = [Service alloc];
    ServiceMyAvaliableProductsResults *r = [s MyAvaliableProducts:date email:self.profile.email];
    
    if (r.Err != nil) {
        NSLog(@"%@", r.Err);
        return;
    }
    allProducts = r.Products;
    
    ServiceMyOrdersResults *r2 = [s MyOrders:date email:self.profile.email];
    
    if (r2.Err != nil) {
        NSLog(@"%@", r.Err);
        return;
    }
    myOrderedProducts = r2.Orders;
    
    [self.tableView reloadData];
}

- (void)viewWillAppear:(BOOL)animated {
    if (self.currentDate == nil) {
        self.currentDate = [NSDate date];
    }
    [self refetchData:[[Profile dateFormatter] stringFromDate:self.currentDate]];
}

- (IBAction)nextDay:(id)sender {
    self.currentDate = [self.currentDate dateByAddingTimeInterval:3600*24];
    [self refetchData:[[Profile dateFormatter] stringFromDate:self.currentDate]];
}

- (IBAction)previousDay:(id)sender {
    self.currentDate = [self.currentDate dateByAddingTimeInterval:-3600*24];
    [self refetchData:[[Profile dateFormatter] stringFromDate:self.currentDate]];
    
}



- (void)viewDidLoad
{
    [super viewDidLoad];
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
