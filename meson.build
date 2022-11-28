project('flashcards', 'c', version : '1.0', license : 'GPL-3.0-or-later')

gtk_dep = dependency('gtk4')
libadwaita_dep = dependency('libadwaita-1', version: '>=1.2')
sqlite_dep = dependency('sqlite3')

gnome = import('gnome')

subdir('po')
subdir('src')
subdir('resources')

executable('flashcards',
  sourcefiles,
  resources,
  schemas,
  dependencies: [gtk_dep, libadwaita_dep, sqlite_dep],
  install: true
)