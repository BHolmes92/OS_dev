void main(){
    //Pointer to video memory region
    char* video_memory = (char*) 0xb8000;
    //Set 'X' to initial video position
    *video_memory = 'X';
}