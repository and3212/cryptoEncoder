# Crypto Key Encoder
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

If you are invested in crypto you are either worried that you will lose your crypto key, or that someone will steal it online. This project is here to fix both of these problems. The best way to have peace of mind is to hide your key in plain sight, in a spot so obvious no one would even think to look there, and even if someone did find it they would have no idea how to access your accounts. Now you can hide your sensitive crypto phrases inside an image that you can safely upload to the cloud with peace of mind that no one will ever realize it is the key to all of your accounts.

### Prerequisites
Image's have their pixel values modified by OpenCV

[OpenCV](https://github.com/opencv/opencv) - Intel's Open Source Computer Vision Library

### Building
Navigate to the source folder and run the following commands
```
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Files
* single.cpp - Encrypts your key by splitting each char into 8 pixels, modifying the LSB in each pixel
* pairs.cpp - Encrypts your key by splitting each char into 4 pairs of 2, modifying the two LSBs in each pixel
* ascii_to_dec.cpp - Finds the sum of all of the ASCII letters in a word

## How It Works
Crypto keys are 24 words long, randomly chosen from a list according to the [BIP-39](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki) standard. In each word, every letter can be represented in an 8 bit number space using ASCII. For our example let's look at the word ```cat```.

The first thing we want to do is hide the ```c``` in the image. Now, if we just took the ASCII value of ```c``` (which happens to be 99) and replace a pixel with the 99, it would defeat the purpose of hiding in plain sight. Imagine that there are just random dots of color in an image, it could throw some red flags to someone viewing the image and alert them that the image was tampered with.

The way to get around this it to split the letters up into 4 sections. The binary value of ```c``` is ```01100011```. We take these 8 bits and just group them into pairs. So now we have
```
01
10
00
11
```

Instead of replacing an entire pixel with the value of ```c```, we just replace the two least significant bits with one of the pairs. Pixel values (in nearly all images) are 8 bit, which ranges from 0 - 255. This works out perfectly for what we are trying to achieve. Even with the most extreme change of the bits, the value of the pixel would only change by 3, which equates to about a 1% change in the color intensity. This is imperceptible to anyone looking at the image as cameras generally have an error greater than 1% in a region of solid color.

Now we just place each pair for every letter throughout the image until we run out of words, you now have an image encrypted with steganography!

--------------------

**Note:** There is now a version of the encryption code that splits chars up into single bits. This is most likely more secure, it works in the exact same way as stated above except there are 8 sets of 1 bit for every char.

## Randomization
Some may fear that a malicious algorithm could start scraping an image and combining the 2 LSBs from each pixel to form words to steal your data, however there is no reason to worry over your key getting stolen. When encrypting the image, the user is asked for five numbers before anything runs to help keep the data protected.

* X Coordinate
    * The X location where the program starts placing your bit pairs
* Y Coordinate
    * The Y location where the program starts placing your bit pairs
* Random Seed
    * Each pair is a random distance apart from each other to stop malicious algorithms from scrapping images to find your key
    * Each pair is randomly placed on a different color channel of the image. This further helps prevent data theft as there        as there is no order to which color will be modified next out of the red, blue, and green pixels
* Minimum Skip
    * The minimum distance between pairs
* Maximum Skip
    * The maximum distance between pairs. This is can be tweaked if you somehow go out of the bounds of the image and run out        of pixels to use. This must be larger than minimum skip

A normal 1920x1080 image will have over 2 million red, green, and blue pixels, approximately 6 million pixels in all. With your 24 words being randomly spaced and having the pairs be on a random color channel, the odds of finding your phrase is very, very low. **However,** if someone has the original (non-altered) image, they could compare the values to each other and see exactly which ones you modified, which could lead to your data being compromised. To solve this problem, make sure all copies of the original image are deleted from all of your devices.

## Choosing The 5 Numbers
For this program to work, you need to make sure you have the 5 numbers recorded. If you are really too paranoid to write these down, try using a book for the phrases. The best kind is one that does not have different editions, as you could lose your numbers too easily. Try going for something like the King James version of the Bible, it has stayed constant for hundreds of years and won't be changing anytime soon. Make a note of some verse and just use every nth word as your numbers. There is a file included that you can run with ```./ascii2dec``` that will let you convert your words into numerical values.

## Getting Started
* Make sure your image is in .PNG format, .JPG will not work as it is not lossless and your data will be corrupted
* Rename your file to encrypt.png
* Place the image in the **res/** folder
* Run the program using either ```./singleEncrypt``` or ```./pairEncrypt```
* Select Encryption mode and follow the instructions
* (Optional) Record the total number of characters in your phrase - This is not crucial as you can always enter a number        larger than you need, it is just to keep everything looking nice
* Verify that you can get your data back out of the image by running the program again but in Decrypt mode
* Delete encrypt.png and any copies that you may have of the image
* Rename decrypt.png to something normal and upload it to the cloud

## License

This project is licensed under the GPL v3 License - see the [LICENSE.md](LICENSE.md) file for details

## Liability
The developers, maintainers, contributors, and operators are to not be held liable for any personal damages or loss related to the use of this program. This project was done for fun, be smart about keeping your sensitive data safe. If you want to be sane and encrypt your passphrase in a much less convoluted way, please check out [GPG encryption.](https://gnupg.org/)
