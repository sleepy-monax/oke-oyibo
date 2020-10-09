CXXFLAGS+= \
	-g \
	-fsanitize=address \
	-fsanitize=undefined

LDFLAGS+= \
	-fsanitize=address \
	-fsanitize=undefined
