" No annoying sound on errors
set t_vb=
set noerrorbells
set novisualbell
if has("autocmd") && has("gui")
  au GUIEnter * set t_vb=
  au GUIEnter * set noerrorbells
  au GUIEnter * set novisualbell
endif

" Turn backup off, since most stuff is in SVN, git et.c anyway...
set nobackup
set nowb
set noswapfile

" Set smart indentation
set autoindent
set smartindent

" 1 tab == 4 spaces
set shiftwidth=4
set tabstop=4

" colors
let &runtimepath.=','.getcwd().'\.vim'
syntax on
colorscheme monotone
set termguicolors

" make backspace work like most other programs
set backspace=2

" line number
set number

" line hightlighting
set cursorline

" use system clipboard
set clipboard=unnamedplus

" line wrap
set nowrap

" new splits open in right
set splitright

" build
set makeprg=build.bat

" key mapping
nnoremap <F7> :silent make<CR>:copen<CR>
