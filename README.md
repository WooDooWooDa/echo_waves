# Echo Waves
Use echolocalisation waves to navigate throught the levels and find your way out.

## Attributions
All sprites are from [game-icons.net](https://game-icons.net/)

All sounds are from [Pixabay](https://pixabay.com/sound-effects/)

[View more details in my portfolio](https://grateful-quark-516.notion.site/Echo-Waves-2a02e665cdfe80dd9368f24ce9d714ab)

## HOW TO BUILD FOR WEB
1. run "B:\emscripten\emsdk\emcmdprompt.bat" in a POWERSHELL
2. Navigate to the project web build folder using "cd B:\C++_GAMES\echo_waves\web_build"
3. Configure the project with Emscripten using "emcmake cmake .."
4. Build the project using "emmake cmake --build ."
	-> Optional: Clean the build with "cmake --build . --target clean"
5. The compiled web files will be placed in the ".\dist" folder
	-> run the project in local browser with "emrun --port 8080 dist/index.html" from root
