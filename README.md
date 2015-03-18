Rampage
===
Quickly mount/unmount existing folders to RAM

Status: Proof of concept. **DON'T USE THIS YET!**

Stable alternative: [anything-sync-daemon](https://github.com/graysky2/anything-sync-daemon)

Copyright (c) 2014 Grady O'Connell

Think your SSD is fast? PEASANT!
Mount folders in RAM for MAXIMUM SPEED! RAWRRR!!!
Then push back changes when done, merge tool optional.

Platform: Linux

REQUIRES: [kit](http://github.com/flipcoder/kit)

## Usage

**Always back up your data before using a program like this.**

Although not all actions are implmented, below is the intended usage:

###Load a folder into RAM
```
rpg folder
```

###View the status of all rampaged folders
```
rpg -l
```

###View diff between RAM and HD versions
```
rpg -d folder
```

###Write changes (from RAM) back to HD without unmounting
```
rpg -w folder
```

###Discard ALL changes made to RAM version and unmount
```
rpg -r folder
```

If your computer crashes while a folder is rampaged, you will only lose unwritten RAM changes.
The original HD version is stored at *.FOLDER.rpg*. as a backup.  The broken symlink in its
place may be safely deleted.

Right now, folders are rampaged on a folder-name-basis.
You will not yet be able to rampage folders of similar names (yet).

===

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

