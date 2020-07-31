Into the Spiderverse is one of the most breathtaking films I have seen in a while. From the way it is animated to the shaders and effects they used, they crafted a living embodiment of the comic book world. One of the aspects of this film, that I am going to try to recreate in UE4 as a proof of concept, is the Ben Day dots. We will have dots while things are illuminated, and a crosshatching effect when things are in shadow. You can see these effects in the following image:
https://i.pinimg.com/originals/da/b5/e8/dab5e83a65a59de0932988790ffe95cb.jpg


Ben Day vs halftone differences vs Pointillism 
While all these methods might be very similar, they all have very specific differences in how they operate. Ben Day dots are always of equal size and distribution in a specific area. Halftone dots are allowed to vary in size or in spacing and pointillism requires color. So for the sake of clarity and art history, we will be implementing Ben Day dots as our first pass.



Now if I were to write this shader in either OSL for offline rendering, or in a  forward shading environment, I wouldn't have to much difficulty as the we have direct access to lighting vectors. Yet because UE4 uses a deferred render we do not have access to lighting information, so our biggest issue is going to be figuring out how we can place the dots or cross hatching in the correct spot. 

While we dont have access to the lighting vectors in our shaders, if we use a post process material, we CAN see something important and thats the scenes shadows by subtracting the diffuse color from the scene and then desaturating it. For this use case I am also multiplying this result by a parameter to adjust the lighting intensity and then running it through a ceil to clamp everything together. This leaves us with a mask that selects the non shadows of the scene with a parameter to adjust it as necessary. 

![Drag Racing](https://github.com/ntorkildson/GameplaySystems/blob/master/BlogPostImages/MaskingOutShadows.JPG?raw=true)

The great thing about masks is that the inverse of them is also useful sometimes, for this instance the inverse of shadows is the lighting information, or at least we can try to make it work.We invert the shadow  mask and we have the appropriate information for lighting area, again with a parameter to adjust the intensity of the mask.
One of the issues I was noticing in the dots is that objects in the distance had dots that were the same size, which meant the scale was distracting as you moved around. I first attempted to modify this by using the scene depth, but that was finicky and failed to really solve another problem: the dots are mapped to the camera and not to the surfaces of the objects...
Quick fix for this was to use tri-planer mapping for everything, this  puts the texture on all the surfaces and scales for distance. 

This shader ended up taking a bit less than 2 days to implement inside UE4. This includes optimizing editor graphs and making things as adjustable as possible, as well as writing this blog post. It currently takes 2 images, the texture we want to show int he shadow and the texture we want to show in the sunlight as well as parameters for how much overlap on shadows and non shadows we want to have. Im going to say Im done experimenting on this for now, the proof of concept works brilliant. 

Extending this into Halftone dots, , would require an actual dithering effect, which requires a computationally expensive matrix multiplication over the entire image, and while not prohibited in a lot of work Im not sure thats something I want to create in a graph editor....at least not yet. Pointalism could be implemented by adding the diffuse layer overtop our post process effect, we could even do some simple math to allow us to adjust intensity.
I do want to revisit this in the future and test a custom ambient occlusion system for the crosshatching, limiting it to a much smaller area.



![Final Result](https://github.com/ntorkildson/GameplaySystems/blob/master/BlogPostImages/FinalShaderResult.JPG?raw=true)
