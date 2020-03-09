echo "Rimozione file cpp_parameters"
Get-ChildItem  -Include *.cpp_parameters -Recurse | foreach { $_.Delete()}
echo "Rimozione file cbp"
Get-ChildItem  -Include *.cbp -Recurse | foreach { $_.Delete()}
echo "Rimozione file depends"
Get-ChildItem  -Include *.depends -Recurse | foreach { $_.Delete()}
echo "Rimozione file CMakeCache"
Get-ChildItem  -Include CMakeCache.txt -Recurse | foreach { $_.Delete()}
echo "Rimozione file ui_*"
Get-ChildItem  -Include ui_* -Recurse | foreach { $_.Delete()}
echo "Rimozione file Makefile"
Get-ChildItem  -Include Makefile -Recurse | foreach { $_.Delete()}
echo "Rimozione file CMakeFiles"
Remove-Item CMakeFiles -Recurse -Force
Remove-Item src\CMakeFiles -Recurse -Force
Remove-Item xlsx\CMakeFiles -Recurse -Force
echo "Rimozione file _CPack_Packages"
Remove-Item _CPack_Packages -Recurse -Force
echo "Rimozione file CPackConfig.cmake"
Get-ChildItem  -Include CPackConfig.cmake -Recurse | foreach { $_.Delete()}
echo "Rimozione file CPackSourceConfig.cmake"
Get-ChildItem  -Include CPackSourceConfig.cmake -Recurse | foreach { $_.Delete()}
echo "Rimozione file compile_commands.json"
Get-ChildItem  -Include compile_commands.json -Recurse | foreach { $_.Delete()}
echo "Rimozione file parameter"
Get-ChildItem  -Include *.cxx_parameters -Recurse | foreach { $_.Delete()}
echo "Rimozione file dll"
Get-ChildItem  -Include *.dll -Recurse | foreach { $_.Delete()}
echo "Rimozione file dll.a"
Get-ChildItem  -Include *.dll.a -Recurse | foreach { $_.Delete()}
echo "Rimozione file moc"
Get-ChildItem  -Include moc_* -Recurse | foreach { $_.Delete()}
echo "Rimozione file Makefile"
Get-ChildItem  -Include Makefile -Recurse | foreach { $_.Delete()}
echo "Rimozione file qrc_"
Get-ChildItem  -Include qrc_*.cpp -Recurse | foreach { $_.Delete()}
echo "Rimozione file cmake_install.cmake"
Get-ChildItem  -Include cmake_install.cmake -Recurse | foreach { $_.Delete()}
echo "Rimozione file install_manifest.txt"
Get-ChildItem  -Include install_manifest.txt -Recurse | foreach { $_.Delete()}