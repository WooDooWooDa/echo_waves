---HOW TO BUILD FOR WEB
1. run "B:\emscripten\emsdk\emcmdprompt.bat" in a POWERSHELL
2. Navigate to the project web build folder using "cd B:\C++_GAMES\echo_waves\web_build"
3. Configure the project with Emscripten using "emcmake cmake .."
4. Build the project using "emmake cmake --build ."
	-> Optional: Clean the build with "cmake --build . --target clean"
5. The compiled web files will be placed in the ".\dist" folder
	-> run the project in local browser with "emrun --port 8080 dist/index.html" from root
