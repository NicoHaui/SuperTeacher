# Single download(git clone)
ExternalProject_Add(
    box2d
    URL https://github.com/erincatto/Box2D/archive/v2.3.1.tar.gz
    PREFIX Box2D
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(box2d source_dir)
ExternalProject_Get_Property(box2d binary_dir)

set(BOX2D_INCLUDE_DIRS "${source_dir}/Box2D" CACHE STRING "Box2D include")
set(BOX2D_LIBRARIES "${binary_dir}" CACHE STRING "Box2D Binary")
