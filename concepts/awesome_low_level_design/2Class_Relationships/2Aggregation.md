aggregation is represented by a hollow diamond (◊) on the "whole" side of the relationship. The diamond connects to the class that contains or references the other objects.

Aggregation is a specialized form of association that models a whole-part relationship with loose ownership. One class (the "whole") contains references to other class objects (the "parts"), but the parts can exist independently of the whole.

It's often described as a "has-a" relationship where the whole does not control the part's lifecycle.

EX - 
Artist is an independent entity that creates songs.
Song belongs to an Artist but exists independently of any playlist.
Playlist aggregates multiple Song objects. The same song can appear in different playlists.
User aggregates multiple Playlist objects. Deleting a user's playlist doesn't destroy the songs.
Library holds the master collection of all songs, independent of any playlist or user.

### NOTE: Class diagram is everything, it tells you what to write in code