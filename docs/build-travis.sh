# Create build directory
mkdir -p build
mkdir -p images

# Clean old build file
rm -R build/*

# Copy new file
cp -R images build/
cp *.adoc build/

cd build

# Create rapport.html
asciidoc --backend html5 --theme flask -a toc2 -a icons --section-number rapport.adoc 

cd ..
