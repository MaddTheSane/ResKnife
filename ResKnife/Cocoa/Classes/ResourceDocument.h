#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>	// Actually I only need CarbonCore.framework

@class ResourceWindowController, ResourceDataSource, Resource;

@interface ResourceDocument : NSDocument
{
	IBOutlet ResourceDataSource		*dataSource;
	IBOutlet NSWindow				*mainWindow;
	IBOutlet NSOutlineView			*outlineView;
	
	NSMutableArray	*resources;
	HFSUniStr255	*fork;		// name of fork to save to, usually empty string (data fork) or 'RESOURCE_FORK' as returned from FSGetResourceForkName()
	NSString *creator;
	NSString *type;
}

- (void)setupToolbar:(NSWindowController *)windowController;

- (IBAction)showCreateResourceSheet:(id)sender;
- (IBAction)openResources:(id)sender;
- (void)openResourceUsingEditor:(Resource *)resource;
- (IBAction)openResourcesInTemplate:(id)sender;
- (void)openResource:(Resource *)resource usingTemplate:(NSString *)templateName;
- (IBAction)openResourcesAsHex:(id)sender;
- (void)openResourceAsHex:(Resource *)resource;
- (IBAction)playSound:(id)sender;
- (void)sound:(NSSound *)sound didFinishPlaying:(BOOL)finished;

- (IBAction)clear:(id)sender;

- (void)resourceNameWillChange:(NSNotification *)notification;
- (void)resourceIDWillChange:(NSNotification *)notification;
- (void)resourceTypeWillChange:(NSNotification *)notification;
- (void)resourceAttributesWillChange:(NSNotification *)notification;

- (BOOL)readResourceMap:(SInt16)fileRefNum;
- (BOOL)writeResourceMap:(SInt16)fileRefNum;

- (NSWindow *)mainWindow;
- (ResourceDataSource *)dataSource;
- (NSOutlineView *)outlineView;
- (NSArray *)resources;		// return the array as non-mutable

- (NSString *)creator;
- (NSString *)type;
- (IBAction)creatorChanged:(id)sender;
- (IBAction)typeChanged:(id)sender;
- (void)setCreator:(NSString *)oldCreator;
- (void)setType:(NSString *)oldType;
- (void)setCreator:(NSString *)newCreator andType:(NSString *)newType;

@end
