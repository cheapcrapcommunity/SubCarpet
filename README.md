# SubCarpet

A small Audio_visual programme applying displacement mapping data into sonification.

## Install

How to run:
Use ProjectGenerator for openframeworks to import the file folder 'SubCarpet', select 'ofxMaxim' from the drop down list of Addons.

Watch demo on Youtube: https://www.youtube.com/watch?v=1Xhxq5NCvMQ


## Description

This program uses the openFrameworks to create an interactive audio-visual output that is generated using Perlin noise and frequency modulation (FM) synthesis.
It loads a shader that renders three 3D planes, each of which is mapped with an image generated from Perlin noise. It can be thought of as a form of displacement mapping. By varying the brightness values of the pixels in the image, the displacement of the vertices of the planes is varied, resulting in the appearance of a complex, dynamic surface. I generate some noise data and store it in a texture to then use it as a displacement value to move vertices in our vertex shader.

The brightness of each pixel in the image is later mapped to 3 different scales of frequency value that is used for FM synthesis. The freq variable is the carrier frequency and the osc2.sinewave(freq2*osc3.sinewave(freq3)) term is the modulator.

Using FM synthesis can make the frequency changes more pronounced and interesting. The settings of freq = pixels[i]/3; freq2 = pixels[i]/2; freq3 = pixels[i]; correspond to the sizes of the three planes, so the sound changes corresponding to the recessed and dark parts are very sensitive. The mapped frequencies are symmetrical and panning is set.

In summary, the program uses Perlin noise to generate an image that is mapped onto 3D planes, and the brightness of the pixels in the image is mapped to frequency values for FM synthesis.
