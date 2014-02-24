//
//  NMCPlatformView.m
//  PlatformTest0
//
//  Created by Bill on 2/23/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#import "NMCPlatformView.h"
#import "leds.h"
#import "corners.h"

const int VERTEX_SIZE = 6;
const int LEDS = 219;
@interface NMCPlatformView ()

@property NSInteger frameCount;
@property NSMutableArray *colors;
@end

@implementation NMCPlatformView


- (UIColor *) randomColor {
    switch (rand() & 0x3) {
            
        case 0:
        case 1:
            return  [UIColor redColor];
            break;
        case 2:
            return [UIColor orangeColor];
            break;
        case 3:
            return [UIColor yellowColor];
            break;
        default:
            return[UIColor blueColor] ;
            
    }
    
}

- (void) initialize{
    //init your ivars here
    self.frameCount = 0;
    self.colors = [[NSMutableArray alloc]initWithCapacity:LEDS];
    for(int i = 0; i < LEDS; i++) {
        
        switch (rand() & 0x1) {
                
            case 0:
                [self.colors addObject: [UIColor clearColor] ];
                break;
            case 1:
                [self.colors addObject: [self randomColor] ];
                break;
                
        }
    }
    NSLog(@"num colors: %lu", (unsigned long)self.colors.count);
    
}

- (void)tap {
    for(int i = 0; i < 12; i++) {
        int p = (random() & 0xffffff) & LEDS;
        self.colors[p] = [self randomColor];
        
    }
}
- (id) initWithCoder:(NSCoder *)aCoder{
    if(self = [super initWithCoder:aCoder]){
        [self initialize];
    }
    return self;
}

- (id) initWithFrame:(CGRect)rect{
    if(self = [super initWithFrame:rect]){
        [self initialize];
    }
    return self;
}






- (void)animationTimerDidFire:(NSTimer *)timer
{
    [self setNeedsDisplay];
}

- (UIColor *)darkerColorForColor:(UIColor *)c
{
    CGFloat r, g, b, a;
    if ([c getRed:&r green:&g blue:&b alpha:&a]) {
        if (r < 0.1 && g < 0.1 && b < 0.1)
            return [UIColor clearColor];
        return [UIColor colorWithRed:MAX(r - 0.01, 0.0)
                               green:MAX(g - 0.01, 0.0)
                                blue:MAX(b - 0.01, 0.0)
                               alpha:a];
    }
    return nil;
}


- (void)drawRect:(CGRect)rect
{
    // Drawing code
    //    NSLog(@"Drawing %d", self.frameCount);
    
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    // The value we subtract from the height is the Y coordinate for the *bottom* of the image.
	CGContextTranslateCTM(context, self.bounds.size.width/2, self.bounds.size.height/2);
	CGContextScaleCTM(context, 0.25, 0.25);
    UIColor* wood = [[UIColor alloc]initWithRed:0.3  green:0.2 blue:0.1 alpha:1.0];
    
    CGContextSetLineWidth(context, 2.0);
    CGContextSetStrokeColorWithColor(context, wood.CGColor);
    CGContextSetFillColorWithColor(context, wood.CGColor);
    
    CGContextMoveToPoint(context,  Corners[5][0],  Corners[5][1]);
    for(int i = 0; i <= 5; i++)
        CGContextAddLineToPoint(context, Corners[i][0],Corners[i][1]);
    
    CGContextFillPath(context);
    CGContextSetFillColorWithColor(context, [UIColor
                                             whiteColor].CGColor);
    
    for(int i = 0; i < 219; i++) {
        
        int colorIndex = (i + self.frameCount) % LEDS;
        UIColor *color = self.colors[colorIndex];
        if (color == [UIColor clearColor] ) continue;
        CGContextSetFillColorWithColor(context,color.CGColor);
        color = [self darkerColorForColor:color];
        self.colors[colorIndex] = color;
        
        
        CGRect rect = CGRectMake(ledPositions[i][0]-VERTEX_SIZE,ledPositions[i][1]-VERTEX_SIZE, 2*VERTEX_SIZE,2*VERTEX_SIZE);
        
        CGContextFillRect( context, rect);
        
    }
    
    
    self.frameCount++;
    
}



@end
