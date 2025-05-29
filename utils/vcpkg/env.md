### vcpkg

https://github.com/microsoft/vcpkg

```cmd
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg; .\bootstrap-vcpkg.bat
```



```cmd
.\bootstrap-vcpkg.bat
```

添加环境变量



```cmd
vcpkg install <package>
vcpkg remove <package>
vcpkg list
vcpkg search <package>
vcpkg update

vcpkg install --triplet <triplet> --manifest-root <path_to_directory>
```

