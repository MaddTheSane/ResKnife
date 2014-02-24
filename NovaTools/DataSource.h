#import <Cocoa/Cocoa.h>

@interface DataSource : NSObject <NSComboBoxDataSource, NSComboBoxDelegate>
{
	NSString *type;
	NSMutableDictionary *data;
	NSMutableArray *parsed;		// a subset of data, parsed to contain the typed string
}

- (id)initForType:(NSString *)typeString;

- (NSDictionary *)data;
- (void)setData:(NSMutableDictionary *)newData;
- (void)setString:(NSString *)newData forResID:(int)resID;
- (void)parseForString:(NSString *)string sorted:(BOOL)sort;
- (void)parseForString:(NSString *)string withinRange:(NSRange)resIDRange sorted:(BOOL)sort;
- (id)objectValueForResID:(NSNumber *)resID;
- (NSString *)stringValueForResID:(NSNumber *)resID;
+ (NSNumber *)resIDFromStringValue:(NSString *)string;
+ (NSString *)resNameFromStringValue:(NSString *)string;

@end
