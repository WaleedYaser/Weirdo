" set runtime path
set rtp+=~\.fzf
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
let &rtp.=','.getcwd().'\.vim'
syntax on
colorscheme nord
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

" key mapping
	" build
nnoremap <F7> :wa<CR>:set makeprg=build.bat<CR>:silent make<CR>:copen 20<CR>
	" hot reloading kuro
nnoremap <F6> :wa<CR>:set makeprg=kuro\build.bat<CR>:silent make<CR>
	" fuzzy finder
nnoremap <M-p> :FZF<CR>

" Explorer
let g:netrw_banner = 0
let g:netrw_liststyle = 3
let g:netrw_browse_split = 4
let g:netrw_altv = 1
let g:netrw_winsize = 25
