project('dysphoria', 'c')

cc = meson.get_compiler('c')

c_args = []
link_args = []
name_suffix = []
dependencies = []

# Raylib configuration
cmake = import('cmake')
raylib_opts = cmake.subproject_options()
raylib_opts.set_install(false)
raylib_opts.add_cmake_defines(
  {
    'BUILD_EXAMPLES': 'OFF',
    # Add other CMake options for Raylib, if needed
  },
)
if cc.get_id() == 'emscripten'
  raylib_opts.add_cmake_defines(
    {
      'PLATFORM': 'Web',
    },
  )
else
  raylib_opts.add_cmake_defines(
    {
      'PLATFORM': 'Desktop',
    },
  )
endif
raylib_subproject = cmake.subproject('raylib', options: raylib_opts)
dependencies += raylib_subproject.dependency('raylib')

# General configuration
if host_machine.system() == 'windows'
  dependencies += [
    cc.find_library('winmm'),
  ]
  name_suffix = 'exe'
elif host_machine.system() == 'darwin'
  link_args += [
    '-framework', 'AppKit',
    '-framework', 'IOKit',
  ]
elif host_machine.system() == 'linux'
  dependencies += [
    cc.find_library('m'),
    cc.find_library('dl'),
  ]
elif host_machine.system() == 'emscripten'
  link_args += [
    '-s', 'ENVIRONMENT=web',
    '-s', 'USE_GLFW=3',
  ]
  name_suffix = 'html'
endif

# Project files
inc_dir = include_directories(
  'src/includes',
  'src/includes/helpers',
  'src/includes/gameplay',
)

sources = files(
  'src/gameplay/player.c',

  'src/helpers/save/readGameSaveFile.c',
  'src/helpers/save/writeGameSaveFile.c',
  'src/main.c',
  'src/gameplay/cameraSystem.c',

  'src/screens/ending.c',
  'src/screens/intro.c',
  'src/screens/mainMenu.c',
  'src/screens/transition.c',
  
  'src/screens/options.c',

  'src/helpers/save/readGameSaveFile.c',
  'src/helpers/save/writeGameSaveFile.c',
)

executable(
  'dysphoria',
  sources,
  c_args: c_args,
  dependencies: dependencies,
  include_directories: inc_dir,
  link_args: link_args,
  name_suffix: name_suffix,
)