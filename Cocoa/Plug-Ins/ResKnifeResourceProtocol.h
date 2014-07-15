/* =============================================================================
	PROJECT:	ResKnife
	FILE:		ResKnifeResource.h
	
	PURPOSE:	This protocol wraps up whatever implementation the host
				application (i.e. ResKnife) uses for resources in a way that
				every editor can get enough information about the resource
				being edited.
				
				Or in Nick's immortal words (which I found only *after* I had
				written the stuff above):
				
				This protocol allows your plug to interrogate a resource to
				find out information about it.
	
	AUTHORS:	Nick Shanks, nick(at)nickshanks.com, (c) ~2001.
				M. Uli Kusterer, witness(at)zathras.de, (c) 2003.
	
	REVISIONS:
		2003-08-05	UK	Added nameForEditorWindow.
		2003-07-31  UK  Added document accessor, commented.
   ========================================================================== */

#import <Cocoa/Cocoa.h>

@protocol ResKnifeResource <NSObject, NSCopying>
@property NSString *name;
@property OSType type;
@property short resID;
@property unsigned short attributes;
@property NSData *data;
@property (readonly) NSUInteger size;
@property (readonly, getter = isDirty) BOOL dirty;

- (void)touch;

// Prevent a warning
- (id)copy;

- (NSString *)defaultWindowTitle;
- (NSDocument *)document;   // Owner of this resource. Useful for looking for resources in same file as yours.

// These methods are used to retrieve resources other than the one you're editing.
//	Passing a document of nil will indicate to search in all open documents.
//	There is currently no way to search in files which haven't been opened.
//	All returned objects are auoreleased. Retain if you want to keep them.

//	This method may return an empty array
+ (NSArray *)allResourcesOfType:(OSType)typeValue inDocument:(NSDocument *)searchDocument;
//	The next two return the first matching resource found, or nil.
+ (id)resourceOfType:(OSType)typeValue andID:(short)resIDValue inDocument:(NSDocument *)searchDocument;
+ (id)resourceOfType:(OSType)typeValue withName:(NSString *)nameValue inDocument:(NSDocument *)searchDocument;

@end

static inline NSString *GetNSStringFromOSType(OSType theType)
{
	return CFBridgingRelease(UTCreateStringForOSType(theType));
}

static inline OSType GetOSTypeFromNSString(NSString *theString)
{
	return UTGetOSTypeFromString((__bridge CFStringRef)theString);
}

// See note in Notifications.m about usage of these
extern NSString *ResourceWillChangeNotification;
extern NSString *ResourceNameWillChangeNotification;
extern NSString *ResourceTypeWillChangeNotification;
extern NSString *ResourceIDWillChangeNotification;
extern NSString *ResourceAttributesWillChangeNotification;
extern NSString *ResourceDataWillChangeNotification;
extern NSString *ResourceWillBeSavedNotification;

extern NSString *ResourceNameDidChangeNotification;
extern NSString *ResourceTypeDidChangeNotification;
extern NSString *ResourceIDDidChangeNotification;
extern NSString *ResourceAttributesDidChangeNotification;
extern NSString *ResourceDataDidChangeNotification;
extern NSString *ResourceDidChangeNotification;
extern NSString *ResourceWasSavedNotification;
