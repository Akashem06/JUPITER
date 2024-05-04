# SConstruct
import os

###########################################################
# Common FLAGS for Compilation
###########################################################

common_flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-pthread',
    '-Isrc',
    '-Iinc',
    '-Ihal',
    '-Iutils/math',
    '-Iutils/pid',
    '-Ilibs/googletest/googletest/include',
    '-Ilibs/googletest/googlemock/include'
]

###########################################################
# FLAGS for Compilation
###########################################################

cflags = [
    '-Wno-unused-variable',
    '-Wno-unused-parameter',
    '-Wpointer-arith',
]

cppflags = [
    '-Wno-unused-variable',
    '-Wno-unused-parameter',
    '-Wpointer-arith',
]

###########################################################
# Environment Setup
###########################################################

libs_abs_path = os.path.abspath('libs/googletest/build/lib')

env = Environment(
    ENV={ 'PATH': os.environ['PATH'] },
    CC='gcc',
    CXX='g++',
    CXXFLAGS=common_flags + cppflags,
    CCFLAGS=common_flags + cflags,
    LIBS=['gtest', 'gmock'],
    LIBPATH=[libs_abs_path]
)

###########################################################
# Action Functions
###########################################################

COMMAND = COMMAND_LINE_TARGETS[0] if COMMAND_LINE_TARGETS else ''

if COMMAND == 'build':
    SConscript('scons/build.scons', exports={'env': env})

elif COMMAND == 'clean':
    AlwaysBuild(Command('#/clean', [], 'rm -rf build/*'))

elif COMMAND == 'test':
    SConscript('scons/test.scons', exports={'env': env})

elif COMMAND == 'format' or COMMAND == 'lint':
    SConscript('scons/format_lint.scons', exports={'env': env})

elif COMMAND == 'setup':
    SConscript('scons/setup.scons', exports={'env': env})

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
  --test          Run Google Tests
''')
