" build
nnoremap <F7> :wa<CR>:set makeprg=build.bat<CR>:silent make<CR>:copen 20<CR>
" hot reloading kuro
nnoremap <F6> :wa<CR>:set makeprg=kuro\build.bat<CR>:silent make<CR>