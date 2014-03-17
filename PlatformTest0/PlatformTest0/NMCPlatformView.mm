//
//  NMCPlatformView.m
//  PlatformTest0
//
//  Created by Bill on 2/23/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#import "NMCPlatformView.h"
#import "LightModel.h"
#import "leds.h"
#import "corners.h"

const int VERTEX_SIZE = 6;
const int LEDS = 219;
@interface NMCPlatformView () {
    LightModel lightModel;
    long long started;
}


@property NSInteger frameCount;


@end

@implementation NMCPlatformView


- (void) initialize{
     started = (long long)([[NSDate date] timeIntervalSince1970] * 1000.0);
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

- (void)tap: (double) value{
    lightModel.tap(value);
}

- (void)tap {
    [self tap: 1.0];
}

-(double) tempurature {
    return lightModel.temperature;
}

- (void)update
{
    long long now = (long long)([[NSDate date] timeIntervalSince1970] * 1000.0);
    millitime delay =  lightModel.update(now-started);
    [self setNeedsDisplay];
    [self performSelector:@selector(update) withObject:nil afterDelay:delay/1000.0 ];
    NSLog(@"stats %2du %2dt %3dj %4.2faj %3dt\n",
          lightModel.updateRate,
          lightModel.tapRate,
          lightModel.jiggleRate,
          lightModel.avgJiggle,
          (int) (100*lightModel.temperature));
    
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
    lightModel.measureTempurature();
    for(int i = 0; i < 219; i++) {
        
        float h,s,b;
        lightModel.getPixelColor(i,h,s,b);
        
         UIColor *color = [[UIColor alloc]initWithHue:h/360 saturation:s brightness:b alpha:1.0];
        CGContextSetFillColorWithColor(context,color.CGColor);
        
        CGRect rect = CGRectMake(ledPositions[i][0]-VERTEX_SIZE,ledPositions[i][1]-VERTEX_SIZE, 2*VERTEX_SIZE,2*VERTEX_SIZE);
        
        CGContextFillRect( context, rect);
        
    }
    
    
    self.frameCount++;
    
}



@end
