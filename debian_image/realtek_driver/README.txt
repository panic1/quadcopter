I have been following this guide: 
http://bonenotes.tumblr.com/


I bought the LogiLink WL0084A wifi dongle, but it didn't seem to work properly on the beaglebone black.

output from lsusb:
Bus 001 Device 003: ID 0bda:8176 Realtek Semiconductor Corp. RTL8188CUS 802.11n WLAN Adapter

So as suggested by the above mentioned guide I went to http://www.realtek.com.tw/downloads/downloadsView.aspx?Langid=1&PNid=21&PFid=48&Level=5&Conn=4&DownTypeID=3&GetDown=false&Downloads=true
and downloaded the driver for RTL8188CUS

I wanted to compile on the beaglebone, so I didn't need to cross compile.  So I would need the linux kernel headers for the image first as these aren't included in the standard image.
Get them here: http://rcn-ee.net/deb/precise-armhf/v3.8.13-bone50/linux-headers-3.8.13-bone50_1.0precise_armhf.deb

Install the linux headers: dpkg -i linux-headers-3.8.13-bone50_1.0precise_armhf.deb


Copy the realtek driver to the board, unzip, go to the driver directory, unpack and make for ARCH=arm:
unzip RTL8188C_8192C_USB_linux_v4.0.2_9000.20130911.zip
cd RTL8188C_8192C_USB_linux_v4.0.2_9000.20130911/driver
tar xfvz rtl8188C_8192C_usb_linux_v4.0.2_9000.20130911.tar.gz
cd rtl8188C_8192C_usb_linux_v4.0.2_9000.20130911

there is an error in the linux headers:
cd /usr/src/linux-headers-3.8.13-bone50/arch/arm/include/
mkdir mach
touch mach/timex.h
cd -

make ARCH=arm
make install


blacklist the old drivers:
cd /etc/modprobe.d
echo "install rtl8192cu /bin/false" >wifi_blacklist.conf
echo "install rtl8192c_common /bin/false" >>wifi_blacklist.conf
echo "install rtlwifi /bin/false" >>wifi_blacklist.conf



