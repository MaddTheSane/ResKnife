#import "ApplicationDelegate.h"
#import "InfoWindowController.h"
#import "PrefsWindowController.h"
#import "CreateResourceSheetController.h"
#import "ResourceDocument.h"
#import "ResourceDataSource.h"

#import "ResknifePluginProtocol.h"

@implementation ApplicationDelegate

- (id)init
{
	self = [super init];
	[NSApp registerServicesMenuSendTypes:[NSArray arrayWithObject:@"NSString"] returnTypes:[NSArray arrayWithObject:@"NSString"]];
	return self;
}

- (void)awakeFromNib
{
	// Part of my EvilPlan� to find out how many people use ResKnife and how often!
	int launchCount = [[NSUserDefaults standardUserDefaults] integerForKey:@"LaunchCount"];
	[[NSUserDefaults standardUserDefaults] setInteger:launchCount + 1 forKey:@"LaunchCount"];
	
    [self initUserDefaults];
}    

- (IBAction)showAbout:(id)sender
{
	[NSApp orderFrontStandardAboutPanel:sender];
	// get about box code from http://cocoadevcentral.com/tutorials/showpage.php?show=00000041.php
}

- (IBAction)showInfo:(id)sender
{
	[[InfoWindowController sharedInfoWindowController] showWindow:sender];
}

- (IBAction)showPrefs:(id)sender
{
	[[PrefsWindowController sharedPrefsWindowController] showWindow:sender];
}

- (IBAction)showCreateResourceSheet:(id)sender
{
	// requires ALL main windows' controllers (even plugs) to have their document set correctly
	NSDocument *document = [[[NSApp mainWindow] windowController] document];
	return [[[(ResourceDocument *)document dataSource] createResourceSheetController] showCreateResourceSheet:document];
}

- (IBAction)openResource:(id)sender
{
	// bug: only opens the hex editor!
//	NSBundle *hexEditor = [NSBundle bundleWithIdentifier:@"com.nickshanks.resknife.hexadecimal"];
//	NSBundle *hexEditor = [NSBundle bundleWithPath:[[[NSBundle mainBundle] builtInPlugInsPath] stringByAppendingPathComponent:@"Hexadecimal Editor.plugin"]];
	NSBundle *hexEditor = [NSBundle bundleWithPath:[[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Hexadecimal Editor.bundle"]];
//	[hexEditor load];
	
	// bug: possible lack of necessary retains here, esp. resource - should the plug retain it?
	ResourceDocument *resDocument = (ResourceDocument *) [[[NSApp mainWindow] windowController] document];
	Resource *resource = [[resDocument outlineView] itemAtRow:[[resDocument outlineView] selectedRow]];
	// bug: I alloc a plug instance here, but have no idea where it gets dealloc'd
	id hexWindow = [[[hexEditor principalClass] alloc] initWithResource:resource];
}

- (IBAction)playSound:(id)sender
{
}

- (void)initUserDefaults
{
	// This should probably be added to NSUserDefaults as a category,
	//	since its universally useful.  It loads a defaults.plist file
	//	from the app wrapper, and then sets the defaults if they don't
	//	already exist.
	
	NSUserDefaults *defaults;
	NSDictionary *defaultsPlist;
	NSEnumerator *overDefaults;
	id eachDefault;
	
	// this isn't required, but saves us a few method calls
	defaults = [NSUserDefaults standardUserDefaults];
	
	// load the defaults.plist from the app wrapper.  This makes it
	//	easy to add new defaults just using a text editor instead of
	//	hard-coding them into the application
	defaultsPlist = [NSDictionary dictionaryWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"defaults" ofType:@"plist"]];
	
	// enumerate over all the keys in the dictionary
	overDefaults = [[defaultsPlist allKeys] objectEnumerator];
	while( eachDefault = [overDefaults nextObject] )
	{
		// for each key in the dictionary
		//	check if there is a value already registered for it
		//	and if there isn't, then register the value that was in the file
		if( ![defaults stringForKey:eachDefault] )
		{
			[defaults setObject:[defaultsPlist objectForKey:eachDefault] forKey:eachDefault];
		}
	}
	
	// force the defaults to save to the disk
	[defaults synchronize];
}

@end
