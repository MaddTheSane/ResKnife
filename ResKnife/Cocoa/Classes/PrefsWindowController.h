#import <Cocoa/Cocoa.h>

enum DataProtection
{
	preserveBackupsBox = 0,
	autosaveBox,
	deleteResourceWarningBox
};

@interface PrefsWindowController : NSWindowController
{
    IBOutlet NSTextField	*autosaveIntervalField;
    IBOutlet NSMatrix		*dataProtectionMatrix;
}

- (IBAction)acceptPrefs:(id)sender;
- (IBAction)cancelPrefs:(id)sender;
- (IBAction)resetToDefault:(id)sender;

+ (id)sharedPrefsWindowController;

@end