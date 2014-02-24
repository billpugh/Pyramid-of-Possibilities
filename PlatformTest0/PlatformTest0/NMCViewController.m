//
//  NMCViewController.m
//  PlatformTest0
//
//  Created by Bill on 2/23/14.
//  Copyright (c) 2014 Ninja Monkey Coders. All rights reserved.
//

#import "NMCViewController.h"
#import "NMCPlatformView.h"

@interface NMCViewController ()
- (IBAction)didTap:(UITapGestureRecognizer *)sender;
- (IBAction)tapButton:(id)sender;
@property (weak, nonatomic) IBOutlet NMCPlatformView *platformView;

@property (strong, nonatomic)  NSTimer *timer;
@end

@implementation NMCViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    self.timer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self.platformView
                                                selector:@selector(animationTimerDidFire:) userInfo:nil repeats:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)didTap:(UITapGestureRecognizer *)sender {
    NSLog(@"Tap");
    [self.platformView tap];
}

- (IBAction)tapButton:(id)sender {
    [self.platformView tap];
}
@end
