**Welcome to Ubiquitous!**

  Ubiquitous is a tool with algorithms designed to aid generating data of all combinations. The fundamentals of this program are similar to other password cracking software like hashcat but with a few key differences. Ubiquitous introduces static and dynamic place values. This means that the entire password no longer needs to be brute forced if there are place values that are already known. These place values that are already known are referred to as static characters. Any unknown place values are Dynamic place values. The introduction of this feature dramatically decreases the size of password lists while still maintaining reliability. Below is a tutorial on how to use Ubiquitous for list generation and hash collision.
  
**Installation** 

Fork the entire repository and open with visual studio 2022. Or run the code your own personal way. It hopefully shouldn't be too hard. Leave a comment if that is the case. I want this to be easy to run. 
  
**List Generation Tutorial**

When Ubiquitous is launched, the user is promoted to input static and dynamic characters. Static characters do not change when generating possibilities. Dynamic place values do change however. Every possible combination of the dynamic characters will be processed. This step is to initialize the string (or password).

For example, In a situation where some place values of password are already known. The static characters are the place values that are already known. The dynamic place values are all the other unknown place values. 

![UbiquitousSecondStep](https://user-images.githubusercontent.com/92893340/223863415-535bf33d-f74f-44d8-93b6-4e1e13a5dc6a.PNG)

For this example we are going to pretend that we know the first three characters, but not the last four. To specify this the payload will look something like 
"GoD[][][][]". The first three letters being static characters and the last four letters being dynamic. 

![UbiquitousSecondInput](https://user-images.githubusercontent.com/92893340/225156313-3c559ce4-73ac-419a-be88-fde416af2141.PNG)

The next step is to configure the dynamic place values. This is the step where the user decides what values each dynamic place value could hold. The user can input 0 to enter a custom character set or select from pre-made character sets. These sets include structures such as all lower case english letters or the entire ascII character set. It is recommended to use as few characters as possible. Bigger sets have a dramatic effect on processing times. The prompt looks like this. 

![UbiquitousCharacterSet](https://user-images.githubusercontent.com/92893340/223867084-83d782b6-d270-455e-8be5-72dd1fa6a9d8.PNG)

For this demonstration I am going to use option 3 for all lowercase and uppercase letters in english. 

![threeuqiquitous](https://user-images.githubusercontent.com/92893340/223868191-4cbbb445-6b33-4320-8a97-1378350c3b88.PNG)

Next the user will be asked if the output is going to be hashed. Ubiquitous currently only provides an md5 hash but other hashing algorithms will soon be added. For this example the output will not be hashed. Input 0 for no. 

![hashes](https://user-images.githubusercontent.com/92893340/223869157-1a1073b2-b529-47c8-acc7-a1571f9a8559.PNG)

After the hashing question the user will be prompted with another question regarding repeating characters. This is an important question because generating every possible combination can return outputs that are just garbage considering how many characters are repeating. For instance if you are looking for a password that is 8 place values long, the likelihood of that password being 8 characters repeating is very, very unlikely. This functionality was built to skip over iterations that are unlikely to be the password.

![newrepeatsettings](https://user-images.githubusercontent.com/92893340/225162156-542e255a-4ba1-4d5a-ab54-30459a49796c.PNG)

All the configuration information has been set up. All that needs to be done now is to set a range to compute and generate the list! If the user wants every possibility they would enter 1 to start at the beginning. And then enter the same value as work load to run through the last possibility.

![workload](https://user-images.githubusercontent.com/92893340/223873310-28cb9c57-6e42-40da-b21b-555d622c1c86.PNG)

Hit enter and wait for the list to be computed. The text file will appear in the directory that the application is present in. Below is a screenshot of the output file. 

![newoutput](https://user-images.githubusercontent.com/92893340/225162601-b49f5787-4054-49cd-a30f-62523d33cf2c.PNG)

This list can now be used with aircrack-ng or other wordlist attack frameworks! Happy hacking, and good luck friends!

**Collisions -- not currently available due to authenticity of the md5 algorithm used**

To perform a collision, run the program and Answer the first question with Zero for hash collision.

![UbiquitousFirstStep](https://user-images.githubusercontent.com/92893340/223862825-ce4d6af1-09d9-4572-8579-e3e82c5fed20.PNG)

To run this attack the attacker will need an MD5 hash to collide with. This can be obtained through capturing a four way handshake. A good tutorial on how to capture a 4 way handshake can be found here on David Bombal's youtube channel https://www.youtube.com/watch?v=WfYxrLaqlN8. For this demonetisation I have collected a .cap file from an extra router I had laying around. The hash extracted was "5728ed449617ce2ad2106d6ad1cd1560". When Ubiquitous asks for the hash this is what the attacker will input. When prompted to input the hash copy and paste it in.

![zTheRealhash](https://user-images.githubusercontent.com/92893340/225173127-d52c77bf-22d0-459d-b3fe-0d04d773b5f0.PNG)
 
Now let's say an attacker was shoulder surfing and noticed the keyboard click a total of 7 times and noticed the first three letters of the password were GoD. Ubiquitous can generate data for every possible combination beginning with GoD and ending with four dynamic characters. When prompted to do so, the string configuration for this attack would look like so:

![UbiquitousSecondInput](https://user-images.githubusercontent.com/92893340/225156313-3c559ce4-73ac-419a-be88-fde416af2141.PNG)

Next the attacker would need to think about what possible characters could be in the password. He/She notices there are capital and lowercase letters in the beginning so they pick option 3 for lower and uppercase letters.

![UbiquitousCharacterSet](https://user-images.githubusercontent.com/92893340/223867084-83d782b6-d270-455e-8be5-72dd1fa6a9d8.PNG)

When performing hash collisions in Ubiquitous always select yes for hashed output.

![alwayshashed](https://user-images.githubusercontent.com/92893340/225169905-4e3aa6f9-1b30-427d-854f-f0ec4f23683c.PNG)

The attacker can then decide if they want possibilities with repeating place values to be hashed and checked. In this case the attacker allows repeating place values to prevert accidentally skipping over the collision. 

![znever](https://user-images.githubusercontent.com/92893340/225170707-e1a18222-c1b5-46e9-a0e6-1dcf38341d70.PNG)

Finally the attacker inputs what range of values he wants to check and hits enter!

![workload](https://user-images.githubusercontent.com/92893340/223873310-28cb9c57-6e42-40da-b21b-555d622c1c86.PNG)

When Work load is a very large number processing times can be very long. Adding multithreading to the codebase can help this issue. This feature may be added in the near future. 
 
When a collision is found it will inform the user of the hash and the plan text translation. 

![zfoundcollision](https://user-images.githubusercontent.com/92893340/225173453-e248503b-c88e-43db-a6a3-1b64b4d78fa2.PNG)






