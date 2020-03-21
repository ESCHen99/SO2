if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <F2> :wi
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
map <F12> 
map <S-F7> :make clean all
map <F7> :make
map <F6> :Dox
map <F5> :!ctags -R –c++-kinds=+p –fields=+iaS –extra=+q .
map <F4> :e %:p:s,.h$,.X123X,:s,.cpp$,.h,:s,.X123X$,.cpp,
nmap <F2> :w
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set comments=sl:/*,mb:\ *,elx:\ */
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set hlsearch
set printoptions=paper:a4
set ruler
set runtimepath=~/.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim80,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after
set shiftwidth=4
set smartindent
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabstop=2
set tags=./tags,./TAGS,tags,TAGS,~/.vim/tags/cpp,~/.vim/tags/gl,~/.vim/tags/sdl,~/.vim/tags/qt4
set textwidth=120
set window=46
" vim: set ft=vim :
