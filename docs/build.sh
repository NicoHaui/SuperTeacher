# Create build directory
mkdir -p build
mkdir -p images

# Clean old build file
rm -R build/*

# Copy new file
cp -R images build/
cp *.adoc build/

cd build

# Convert PDF to PNG
find . -type f -name '*.pdf' -print0 |
  while IFS= read -r -d '' file
    do convert -verbose -density 150 -rotate 90 "${file}" "${file%.*}.png"
  done

# Create EC_DS2450.html
asciidoc --backend html5 --theme flask -a toc2 -a icons --section-number rapport.adoc 

# Create EC_DS2450.pdf
a2x --no-xmllint -f pdf -d article --dblatex-opts "-P doc.publisher.show=0 --param=latex.encoding=utf8"  rapport.adoc

cd ..
