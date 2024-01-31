## INFO: Make sure that the path to the Arduino libraries is correct on your machine,
## replace if necessary.

FROM := lib
TO := /home/$(USER)/Arduino/libraries

build:
	cp -ru $(FROM)/* $(TO)

.PHONY: build
