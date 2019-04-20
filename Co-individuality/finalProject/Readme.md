# Co-Individuality

### Carla Molins Pitarch


## CONCEPT 

Co-Individuality focuses on the concept of the individual. I investigate a person’s identity, and their relationship with other identities when they feel isolated. I started by thinking about political situation that is creating a fracture in relationships between people. What is happening between Spain and Catalonia currently is affecting daily life, and generating anxiety and uncertainty for most of the population. Although this instance of isolation emerges from a political situation, I don’t want to focus on the conflict. Instead, I want to approach my project from the point of view of a politically uprooted person. My goal is to answer one question: is technology able to represent what happens in the liminal space of communication across a border. This liminal space is where everything is possible: what cannot be real in the current political situation can be real in this space. My answer is creating a shared identity through a telematics experience, connecting two instances of the same OpenFrameworks application using TCP protocol.

The ongoing uncertainty about a possible independence of Catalonia reveals that, in a near future, we could become citizens of everywhere and anywhere at the same time. European indecision to mediate the conversation between Spain and Catalonia may be aggravating this situation. That’s why I would like to work around the idea of a temporary loss of identity. Each individual background shapes this identity in order to keep a connexion with the roots of an entire group alienated in an ephemeral political space.

Moreover, I have still too many question with no answer, or at least the one that I hope to be true. But, what do I have meanwhile besides hope?  Is anyone able to feel as I do? Could there be any connection without any other system involved?


## TECHNICAL APPROACH

As my project takes place simultaneously in two different spaces connected through a network to create just one entity, I was wondering if is it possible to recreate a Limen? ‘Limens’ are ‘threshold’ spaces in which one is neither in nor out (Turner, 1974).

Also, if this could be possible thanks to technology, can technologies make present what is both absent and imaginary?

So, what technology am I using for that?

My answer, again, is a **telematics experience**. To achieve that, I’ll be using OpenFrameworks networked through two different computers with cameras that send bytes of the image to each other, in order to get a blended and distorted output. Both cameras will get real-time images from each side and using a Slit-scan technique decompose each line, send it to the other side and blend it with the line from the other side. The final result will be a combination of both images- people -individuals.

The complete set of the installation consist on two different laptops mirroring the image on an external camera and webcam that will be used as a support and as well as a visual clue for the user.


For creating the final OpenFrameworks application:

My first step was working on the visual different explorations while I was coding that on open frameworks. My main trouble here was to sync both slitScan systems (two different cameras with different frame-rates).

My second step was trying to create the network using ofxNetwork addon and TCP protocol. As starting point I was going to create system working locally on my computer and progressively going to an external connection.

Connecting TCP instances together was not the most difficult part. What it became challenging was sending huge amount of data and receive that as ordered packets in order to construct again the image from the data received.

As I was going to send live video but I wanted to use slitScan in the other end, I decided to send line by line. This ended up being complex, and incomprehensibly frustrating because I was too close but to far at the same time to make it work properly. I was having problems myself to allow the own communication that I was trying to establish.

In addition, I will explain briefly my building the network process:

First, sending a static Image using SendRawbyte, then sending the line number using SendMsg.

One of the last phases was sending the image but getting a lot of loss of data and crashing the application for no reason. I had something missing on my code but I didn’t know what to do.

Finally, thanks to Tyler’s technical help the application was able to send ordered bytes, still with some loss, but an amazing result coming from that rough start.


### Addons used:

 ofxNetwork


### Link to pdf presentation with video, pictures and process.
 
https://drive.google.com/open?id=1jLxR_QEEU2vm6Z40seVv3iekhyFIbDwN

https://vimeo.com/246918365 --> Co-individuality complete video.
https://vimeo.com/247718325 --> TCP Network sending Image.