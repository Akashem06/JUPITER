# SConstruct
import os

###########################################################
# FLAGS for Compilation
###########################################################

cflags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-std=c99',
    '-Wno-discarded-qualifiers',
    '-Wno-unused-variable',
    '-Wno-unused-parameter',
    '-Wpointer-arith',
    '-Isrc',
    '-Iinc',
    '-Ihal'
]

env = Environment(
    ENV={ 'PATH': os.environ['PATH'] },
    CC='gcc',
    CCFLAGS=cflags,
    CPPPATH=[],
    LIBS=[],
)

###########################################################
# Action Functions
###########################################################

COMMAND = COMMAND_LINE_TARGETS[0] if COMMAND_LINE_TARGETS else ''

if COMMAND == 'build':
    SConscript('scons/build.scons', exports={'env': env})

elif COMMAND == 'clean':
    AlwaysBuild(Command('#/clean', [], 'rm -rf build/*'))

elif COMMAND == 'format' or COMMAND == 'lint':
    SConscript('scons/format_lint.scons', exports={'env': env})

else: # Unknown command
    SConscript('scons/build.scons', exports={'env': env})

###########################################################
# Custom Help Function
###########################################################
    
Help('''
Usage:
  scons [OPTIONS]

Options:
  -h, --help      Show this help message
  --clean         Clean the build directory
  --format        Format the code
  --lint          Run linting on the code
  --build         Build the project
''')