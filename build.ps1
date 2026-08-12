cmake --build build --config Release
Copy-Item build\_deps\sfml-build\lib\Release\sfml-*.dll build\Release\ -Force
.\build\Release\Function_renderer.exe
