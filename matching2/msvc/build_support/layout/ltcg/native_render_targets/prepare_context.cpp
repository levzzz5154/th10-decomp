#pragma code_seg(".text$a16prepare")
void SprtCtrlTargetsView::Prepare(int index,int sx,int sy,int sw,int sh,int dx,int dy,int dw,int dh) {
    Flush();
    RenderSurface** output=&primary[index];
    if (*output) Clear(index);
    RenderRect source={sx,sy,sx+sw,sy+sh};
    RenderRect target={dx,dy,dx+dw,dy+dh};
    RenderSurface* back;
    if (data_00491c30->methods->GetBackBuffer(data_00491c30,0,0,0,&back)!=0) return;
    RenderTargetMetadata* dimensions=&metadata[index];
    dimensions->width=dw;
    dimensions->height=dh;
    if (data_00491c30->methods->CreateRenderTarget(data_00491c30,dw,dh,data_00491d14,0,0,1,output,0)==0 ||
        data_00491c30->methods->CreatePlain(data_00491c30,dimensions->width,dimensions->height,data_00491d14,3,output,0)==0) {
        RenderSurface** other=&secondary[index];
        if (data_00491c30->methods->CreatePlain(data_00491c30,dimensions->width,dimensions->height,data_00491d14,3,other,0)==0 &&
            CopySurface_004521d6(*output,0,&target,back,0,&source,0xffffffffU,0)==0)
            CopySurface_004521d6(*other,0,0,*output,0,0,0xffffffffU,0);
    }
    if (back) back->methods->Release(back);
}
#pragma code_seg()
