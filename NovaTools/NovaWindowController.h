#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>
#import "Structs.h"
#import "DataSource.h"

#import "ResKnifePluginProtocol.h"
#import "ResKnifeResourceProtocol.h"

#define localCenter		[NSNotificationCenter defaultCenter]

@interface NovaWindowController : NSWindowController <ResKnifePluginProtocol>
{
	id <ResKnifeResourceProtocol>	resource;
	NSUndoManager					*undoManager;
	//NSNotificationCenter			*localCenter;
	NSBundle						*plugBundle;
	
	DataSource *descriptionDataSource;
	DataSource *governmentDataSource;
	DataSource *pictureDataSource;
	DataSource *planetDataSource;
	DataSource *shipDataSource;
	DataSource *soundDataSource;
	DataSource *spinDataSource;
}
@property (retain) id<ResKnifeResourceProtocol> resource;
@property (retain) NSUndoManager *undoManager;
@property (retain) DataSource *descriptionDataSource;
@property (retain) DataSource *governmentDataSource;
@property (retain) DataSource *pictureDataSource;
@property (retain) DataSource *planetDataSource;
@property (retain) DataSource *shipDataSource;
@property (retain) DataSource *soundDataSource;
@property (retain) DataSource *spinDataSource;

- (IBAction)toggleResID:(id)sender;

- (void)resourceNameDidChange:(NSNotification *)notification;
- (void)saveSheetDidClose:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
- (void)invalidValuesSheetDidClose:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;

@end

@interface NovaWindowController (AbstractNovaMethods)

- (NSDictionary *)validateValues;
- (void)saveResource;

@end