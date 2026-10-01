#pragma code_seg(".text$a14capture")
void NativeRenderManager::Capture(int bank,int index,int sx,int sy,int sw,int sh,int dx,int dy,int dw,int dh) {
    if (!banks[bank]->entries[index].texture) return;
    Flush();
    RenderSurface* back;
    if (data_00491c30->methods->GetBackBuffer(data_00491c30,0,0,0,&back)!=0) return;
    RenderSurface* destination;
    RenderTexture* texture=banks[bank]->entries[index].texture;
    if (texture->methods->GetLevel(texture,0,&destination)==0) {
        RenderRect source={sx,sy,sx+sw,sy+sh};
        RenderRect target={dx,dy,dx+dw,dy+dh};
        CopySurface_004521d6(destination,0,&target,back,0,&source,2,0);
        destination->methods->Release(destination);
    }
    back->methods->Release(back);
}
#pragma code_seg()
