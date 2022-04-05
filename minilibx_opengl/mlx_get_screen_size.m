#import <AppKit/NSScreen.h>
void    mlx_get_screen_size(int *width, int *height)
{
	NSRect disp = [[NSScreen mainScreen] frame];
	*height = (int)disp.size.height;
	*height *= 0.92;
	*width = (int)disp.size.width;
}