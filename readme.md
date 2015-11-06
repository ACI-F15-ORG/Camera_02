## Camera

### Goals:

1. Camera
2. Installation Drawings
3. Read
4. Turning In

#### 1. Camera
Use a still camera, video camera, kinect, leap motion or other image capture device in an interactive/reactive project. This project is required to be at least responsive to a participant.

#### 2. Installation Drawings 
Think about how the ideal setup of your work might be installed/setup in a space. Make a quick diagram (side and/or top perspective) with dimensions and where screens, speakers, computer, camera, misc equipment might be placed. 

#### 3. Read
_Programming Interactivity_, Chapter 14, Motion and Gestures. 

[From A to D and back again](http://simonpenny.net/texts/atod.html)

[Hands Up!](http://www.flong.com/texts/essays/essay_pose/)

[Computer Vision for Artists and Designers](http://www.flong.com/texts/essays/essay_cvad/)

[Informal Catalogue of Slit-Scan Video Artworks and Research](http://www.flong.com/texts/lists/slit_scan/)

[Transforming Mirror](http://www.davidrokeby.com/mirrors.html)

#### 4. Turning In
First is to make your own repository of your project and sync it to github. 

Then, Clone this assignment directory to your computer. From within the folder of the clone, use the terminal. 

Make a branch, replace _your-branch-name_ with something unique, rcsid, etc.

```bash
git branch your-branch-name
```
Checkout _your-branch-name_ so that we're working in that branch.

```bash
git checkout your-branch-name
```

Replace _remote-url_ with something like _https://github.com/shawnlawson/shawnmodule.git_ and _linked-folder-name_ with your name _shawnlawson_

```bash
git submodule add remote-url linked-folder-name
```

Then you'll need to add and commit.

```bash
git commit -a -m 'adding submodule'
```

You'll need to push your branch to the remote.

```bash
git push origin your-branch-name
```
You may run up against a GIT 2.0 error. 
http://stackoverflow.com/questions/13148066/warning-push-default-is-unset-its-implicit-value-is-changing-in-git-2-0

Do the simple solution

```bash
git config --global push.default simple
```

From the github web interface for this assignment's repository you'll create a new pull request.

Base will be master, compare will be _your-branch-name_

Create the request. You shouldn't accept your own pull request. Someone else, me or another person, should review the request to make sure none of the other files in the repository were modified before accepting. Sort of like a checks and balances system. 

__Warning__ you can only push if you're a member of our organization. And, do not delete anything from the repository before pushing.