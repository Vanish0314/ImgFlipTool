set_languages("c++17")

-- set_toolchains("mingw-w64")

add_requires("libjpeg")
add_requires("libpng")
add_requires("cimg")

target("flip_images_cimg")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("libjpeg","libpng","cimg")