//
//  NMCViewController.m
//  PlatformTest0
//
//  Created by Bill on 2/23/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#import "NMCViewController.h"
#import "NMCAppDelegate.h"
#import "NMCPlatformView.h"
#import "AccelerometerFilter.h"

#define kUpdateFrequency	100

@interface NMCViewController ()
- (IBAction)didTap:(UITapGestureRecognizer *)sender;
- (IBAction)tapButton:(id)sender;
@property (weak, nonatomic) IBOutlet UITextField *temperatureDisplay;
@property (weak, nonatomic) IBOutlet NMCPlatformView *platformView;

@property (strong, nonatomic) HighpassFilter * highpassFilter;


@end

@implementation NMCViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    self.highpassFilter = [[HighpassFilter alloc] initWithSampleRate:kUpdateFrequency cutoffFrequency:5.0];
    CMMotionManager *mManager = [(NMCAppDelegate *)[[UIApplication sharedApplication] delegate] sharedManager];
    NMCViewController * __weak weakSelf = self;
    if ([mManager isAccelerometerAvailable] == YES) {
        [mManager setAccelerometerUpdateInterval:0.01 + 1/kUpdateFrequency];
        [mManager startAccelerometerUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:^(CMAccelerometerData *accelerometerData, NSError *error) {
            [weakSelf.highpassFilter addAcceleration:accelerometerData];
            double value = 10.0*weakSelf.highpassFilter.norm;
            for(int i = 0; i < 5; i++)
                [weakSelf.platformView tap: value ];
            NSString* tapString = [[NSString alloc] initWithFormat:@"%f %f", weakSelf.platformView.tempurature, value];
            [weakSelf.temperatureDisplay setText: tapString];
            
        }];
    }

    [self.platformView update];
   }

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)didTap:(UITapGestureRecognizer *)sender {
    [self.platformView tap];
}

- (IBAction)tapButton:(id)sender {
    [self.platformView tap];
}
@end
