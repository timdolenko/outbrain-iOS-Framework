//
//  SFWidget.h
//  OutbrainSDK
//
//  Created by Oded Regev on 27/06/2021.
//  Copyright © 2021 Outbrain. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

#import "SFWidgetTableCell.h"
#import "SFWidgetCollectionCell.h"

NS_ASSUME_NONNULL_BEGIN

@protocol SFWidgetDelegate <NSObject>

/**
 *  @brief called on recommendation "click" inside the feed. Publisher should open the URL in an external browser.
 *
 *  @param url - the "click URL" of the recommendation, the publisher should open the URL in an external browser.
 */
- (void) onRecClick:(NSURL * _Nonnull) url;

@optional

/**
 *  @brief (Optional) called when the "feed widget" inside the WebView changed its height. Publisher might want to be notified when the SFWidget changes its height.
 */
- (void) didChangeHeight;

/**
 *  @brief (Optional) publisher may choose to "catch" clicks on "organic recommendations" in order to navigate the user to the clicked recommendation INSIDE the app (instead of the default behavior of openning the link in an external browser)
 *
 *  @param url - the organic rec "article url", i.e. the aricle url we should navigate to within the app navigation stack.
 */
- (void) onOrganicRecClick:(NSURL * _Nonnull) url;

@end

extern NSString * _Nonnull const SFWIDGET_T_PARAM_NOTIFICATION;


@interface SFWidget : UIView

@property (nonatomic, strong) WKWebView *webview;

-(void) configureWithDelegate:(id<SFWidgetDelegate> _Nonnull)delegate url:(NSString * _Nonnull)url widgetId:(NSString * _Nonnull)widgetId installationKey:(NSString * _Nonnull)installationKey;

/**
 *  @brief configure SFWidget with the relevant params for displaying the feed
 *
 *
 *  @note Call this method to configure and initiate the load of the first chunk of the feed.
 *
 *  @param delegate - the instance which implements SFWidgetDelegate (mainly to "catch" click events on a recommendation in the feed)
 *  @param url - the "article url" param, i.e. the current publisher page url in which we display the feed
 *  @param widgetId - the widget_id for the feed widget (for example "MB_1")
 *  @param widgetIndex - should be = 0 if there one widget on the page, or else, if there are 2 widgets on the same page, the second widget will have idx=1
 *  @param installationKey - the publisher "installation key" as received by the account manager in Outbrain
 *  @param userId - should be nil - unless the publisher wants to set a custom userId AND received the approval for data collection from the user.
 *  @param darkMode - should be "false" , unless the publisher wants the display the feed in "dark mode".
 *
 */

-(void) configureWithDelegate:(id<SFWidgetDelegate> _Nonnull)delegate url:(NSString * _Nonnull)url widgetId:(NSString * _Nonnull)widgetId widgetIndex:(NSInteger)widgetIndex installationKey:(NSString * _Nonnull)installationKey userId:(NSString * _Nullable)userId darkMode:(BOOL)darkMode;

- (void)scrollViewDidScroll:(UIScrollView *)scrollView;

- (CGFloat) getCurrentHeight;

- (void)viewWillTransitionToSize:(CGSize)size
       withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator;

-(void) willDisplaySFWidgetTableCell:(SFWidgetTableCell *)cell;

-(void) willDisplaySFWidgetCollectionCell:(SFWidgetCollectionCell *)cell;

@end

NS_ASSUME_NONNULL_END
