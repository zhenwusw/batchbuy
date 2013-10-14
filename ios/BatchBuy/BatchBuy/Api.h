// Generated by github.com/hypermusk/hypermusk
// DO NOT EDIT

#import <Foundation/Foundation.h>


@interface Api : NSObject
@property (nonatomic, strong) NSString * BaseURL;
@property (nonatomic, assign) BOOL Verbose;
+ (Api *) get;

@end



// --- Product ---
@interface Product : NSObject

@property (nonatomic, strong) NSString * Id;
@property (nonatomic, strong) NSString * Name;
@property (nonatomic, strong) NSString * PhotoLink;
@property (nonatomic, strong) NSNumber * Price;
@property (nonatomic, strong) NSString * ValidFrom;
@property (nonatomic, strong) NSString * ValidTo;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- User ---
@interface User : NSObject

@property (nonatomic, strong) NSString * Name;
@property (nonatomic, strong) NSString * Email;
@property (nonatomic, strong) NSString * AvatarLink;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- ProductInput ---
@interface ProductInput : NSObject

@property (nonatomic, strong) NSString * Name;
@property (nonatomic, strong) NSNumber * Price;
@property (nonatomic, strong) NSString * PhotoLink;
@property (nonatomic, strong) NSString * ValidFrom;
@property (nonatomic, strong) NSString * ValidTo;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- UserInput ---
@interface UserInput : NSObject

@property (nonatomic, strong) NSString * Name;
@property (nonatomic, strong) NSString * Email;
@property (nonatomic, strong) NSString * AvatarLink;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- Order ---
@interface Order : NSObject

@property (nonatomic, strong) NSString * Date;
@property (nonatomic, strong) Product * Product;
@property (nonatomic, strong) NSArray * Users;
@property (nonatomic, strong) NSNumber * Count;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end


// === Interfaces ===


// --- PutProductParams ---
@interface ServicePutProductParams : NSObject

@property (nonatomic, strong) NSString * Id;
@property (nonatomic, strong) ProductInput * Input;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- PutProductResults ---
@interface ServicePutProductResults : NSObject

@property (nonatomic, strong) Product * Product;
@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- RemoveProductParams ---
@interface ServiceRemoveProductParams : NSObject

@property (nonatomic, strong) NSString * Id;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- RemoveProductResults ---
@interface ServiceRemoveProductResults : NSObject

@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- PutUserParams ---
@interface ServicePutUserParams : NSObject

@property (nonatomic, strong) NSString * Email;
@property (nonatomic, strong) UserInput * Input;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- PutUserResults ---
@interface ServicePutUserResults : NSObject

@property (nonatomic, strong) User * User;
@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- RemoveUserParams ---
@interface ServiceRemoveUserParams : NSObject

@property (nonatomic, strong) NSString * Email;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- RemoveUserResults ---
@interface ServiceRemoveUserResults : NSObject

@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- PutOrderParams ---
@interface ServicePutOrderParams : NSObject

@property (nonatomic, strong) NSString * Date;
@property (nonatomic, strong) NSString * Email;
@property (nonatomic, strong) NSString * ProductId;
@property (nonatomic, strong) NSNumber * Count;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- PutOrderResults ---
@interface ServicePutOrderResults : NSObject

@property (nonatomic, strong) Order * Order;
@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- RemoveOrderParams ---
@interface ServiceRemoveOrderParams : NSObject

@property (nonatomic, strong) NSString * Date;
@property (nonatomic, strong) NSString * Email;
@property (nonatomic, strong) NSString * ProductId;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- RemoveOrderResults ---
@interface ServiceRemoveOrderResults : NSObject

@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- ProductListOfDateParams ---
@interface ServiceProductListOfDateParams : NSObject

@property (nonatomic, strong) NSString * Date;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- ProductListOfDateResults ---
@interface ServiceProductListOfDateResults : NSObject

@property (nonatomic, strong) NSArray * Products;
@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- OrderListOfDateParams ---
@interface ServiceOrderListOfDateParams : NSObject

@property (nonatomic, strong) NSString * Date;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end

// --- OrderListOfDateResults ---
@interface ServiceOrderListOfDateResults : NSObject

@property (nonatomic, strong) NSArray * Orders;
@property (nonatomic, strong) NSError * Err;

- (id) initWithDictionary:(NSDictionary*)dict;
- (NSDictionary*) dictionary;

@end


@interface Service : NSObject
- (NSDictionary*) dictionary;


- (ServicePutProductResults *) PutProduct:(NSString *)id input:(ProductInput *)input;

- (NSError *) RemoveProduct:(NSString *)id;

- (ServicePutUserResults *) PutUser:(NSString *)email input:(UserInput *)input;

- (NSError *) RemoveUser:(NSString *)email;

- (ServicePutOrderResults *) PutOrder:(NSString *)date email:(NSString *)email productId:(NSString *)productId count:(NSNumber *)count;

- (NSError *) RemoveOrder:(NSString *)date email:(NSString *)email productId:(NSString *)productId;

- (ServiceProductListOfDateResults *) ProductListOfDate:(NSString *)date;

- (ServiceOrderListOfDateResults *) OrderListOfDate:(NSString *)date;
@end

