**Welcome to Ubiquitous!**

  Ubiquitous is a tool with algorithems designed to aid generating data of all combinations. The fundimentals of this program are similar to other password cracking software like hashcat but with a few key differences. Ubiquitous introduces static and dynamic place values. This means that the entire password no longer needs to be brute forced if there are place values that are already known. These place values that are already known are refered to as static characters. Any unknown place values are Dynamic place values. The introduction of this feature dramatically decreades the size of password lists while still maintaining reliability. Below is a tutirial on how to use Ubiquitous for list generation and hash collision.
  
**List Generation Tutorial**

When Ubiquitous is launched the user is prometed to either input 0 for collision or 1 for list generation. Input one and press enter.
  
![UbiquitousFirstStep](https://user-images.githubusercontent.com/92893340/223862825-ce4d6af1-09d9-4572-8579-e3e82c5fed20.PNG)

The next step is to indicate static and dynamic characters. The user will be prompted with this message. 

![UbiquitousSecondStep](https://user-images.githubusercontent.com/92893340/223863415-535bf33d-f74f-44d8-93b6-4e1e13a5dc6a.PNG)

For this example we are going to pretend that we know the first three characters, but not the last four. To specify this the payload will look something like 
"GoD[][][][]". The first three letters being static characters and the last four letters being dynamic. 

![UbiquitousSecondInput](https://user-images.githubusercontent.com/92893340/225156313-3c559ce4-73ac-419a-be88-fde416af2141.PNG)

The next step is to configure the dynamic place values. This is the step where the user decides what values each dynamic place value could hold. The user can input 0 to enter a custome character set or select from pre made character sets. These sets include structures such as all lower case english letters or the entire ascII character set. It is recomended to use as little characters as possible. Bigger sets have a dramatic affect on processing times. The prompt looks like this. 

![UbiquitousCharacterSet](https://user-images.githubusercontent.com/92893340/223867084-83d782b6-d270-455e-8be5-72dd1fa6a9d8.PNG)

For this demonstration I am going to use the option 3 for all lowercase and uppercase letters in english. 

![threeuqiquitous](https://user-images.githubusercontent.com/92893340/223868191-4cbbb445-6b33-4320-8a97-1378350c3b88.PNG)

Next the user will be asked if the output is going to be hashed. Ubiquitous currently only provides an md5 hash but other hasing algorithems will soon be added. For this example the output will not be hashed. Input 0 for no. 

![hashes](https://user-images.githubusercontent.com/92893340/223869157-1a1073b2-b529-47c8-acc7-a1571f9a8559.PNG)

After the hashing question the user will be prompted with another question regarding repeating characters. This is an important question because generating every possible combination can return outputs that are just garbage considering how many characters are repeating. For instance if you are looking for a password that is 8 place values long, the likelyhood of that password being 8 characters repeating is very, very unlikly. This functionality was built to skip over itterations that are unlikly the password.

![newrepeatsettings](https://user-images.githubusercontent.com/92893340/225162156-542e255a-4ba1-4d5a-ab54-30459a49796c.PNG)

All the configuration infromation has ben setup. All that needs to be done now is to set a range to compute and generate the list! If the user wants every posability they would enter 1 to start at the begining. And then enter the same value as work load to run throught the last posability.

![workload](https://user-images.githubusercontent.com/92893340/223873310-28cb9c57-6e42-40da-b21b-555d622c1c86.PNG)

Hit enter and wait for the list to be computed. The text file will apear in the directory that the applcation is present in. Below is a screenshot of the output file. 

![newoutput](https://user-images.githubusercontent.com/92893340/225162601-b49f5787-4054-49cd-a30f-62523d33cf2c.PNG)

This list can now be used with aircrack-ng or other wordlist attack frameworks! Happy hacking, and good luck friends!

**Collisions**

To perform a collision, run the program and Answer the first question with Zero for hash collision.

![UbiquitousFirstStep](https://user-images.githubusercontent.com/92893340/223862825-ce4d6af1-09d9-4572-8579-e3e82c5fed20.PNG)

To run this attack the attacker will need an MD5 hash to collide with. This can be obtained through capturing a four way handshake. A good tutorial on how to capture a 4 way handshake can be found here on david Bombal's youtube channel https://www.youtube.com/watch?v=WfYxrLaqlN8. For this demonistation I have collected a .cap file from an extra router I had laying around. The hash extracted was "43f2d9ff4ed690ebee7b03bf39a4fc00". When Ubiquitous asks for the hash this is what the attacker will input. When prompted to input the hash copy and past it in.

 ![hashinputyum](https://user-images.githubusercontent.com/92893340/225168124-72b9fdf2-0b08-46f2-be57-4c3c5aeb3b59.PNG)
 
 





