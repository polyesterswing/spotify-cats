# Spotify + Cats
This project replaces album images with cat pictures using the `cataas.com` API for cat images.
It hooks `cef_urlrequest_create` and replaces requests to `https://i.scdn.co/image/*` with calls to `https://cataas.com/cat`

# Usage
- You can do `make run` to launch spotify with the shared library loaded in.
- Make sure to clear your icon cache from the spotify application.
- Only tested on linux.

# Picture
![image](https://github.com/polyesterswing/spotify-cats/assets/67583328/0928d1c0-cd49-4d87-bc1b-dd8dc34b1509)
