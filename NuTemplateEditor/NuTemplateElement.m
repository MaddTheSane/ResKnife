//
//  NuTemplateElement.m
//  ResKnife (PB2)
//
//  Created by Uli Kusterer on Mon Aug 04 2003.
//  Copyright (c) 2003 M. Uli Kusterer. All rights reserved.
//

#import "NuTemplateElement.h"


@implementation NuTemplateElement

+(id)	elementForType: (NSString*)t withLabel: (NSString*)l
{
	return [[[self alloc] autorelease] initForType:t withLabel:l];
}

-(id)	initForType: (NSString*)t withLabel: (NSString*)l
{
	if( self = [super init] )
	{
		label = [l retain];
		type = [t retain];
	}
	
	return self;
}

-(void)	dealloc
{
	[label release];
	[type release];
	
	[super dealloc];
}

-(id)	copyWithZone: (NSZone*)zone
{
	NuTemplateElement*	el = [[[self class] allocWithZone: zone] initForType: type withLabel: label];
	//NuTemplateElement*	el = [[[self class] alloc] initForType:type withLabel:label];
	
	return el;
}



-(void)			setType:(NSString*)t
{
	[t retain];
	[type release];
	type = t;
}

-(NSString*)	type
{
	return type;
}

-(void)			setLabel:(NSString*)l
{
	[l retain];
	[label release];
	label = l;
}

-(NSString*)	label
{
	return label;
}


-(int)	subElementCount
{
	return 0;
}

-(NuTemplateElement*)	subElementAtIndex: (int)n
{
	return nil;
}

-(void)	readSubElementsFrom: (NuTemplateStream*)stream
{
	// By default, items don't read any sub-elements.
}


-(void)	readDataFrom: (NuTemplateStream*)stream containingArray: (NSMutableArray*)containing
{
	// You should read whatever kind of data your template field stands for from "stream"
	//	and store it in an instance variable.
}


// Before writeDataTo: is called, this is called to calculate the final resource size:
//	Items with sub-elements should return the sizes of all their sub-elements here as well.
-(unsigned int)			sizeOnDisk
{
	return 0;
}

-(void)					writeDataTo: (NuTemplateStream*)stream
{
	// You should write out your data here.
}


-(NSString*)	stringValue
{
	return @"<unknown>";
}



@end