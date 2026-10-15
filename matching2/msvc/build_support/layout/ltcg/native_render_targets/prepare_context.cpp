#pragma code_seg(".text$a16prepare")
void SprtCtrlTargetsView::Prepare(int index,int sx,int sy,int sw,int sh,int dx,int dy,int dw,int dh) {
    Flush();
    RenderSurface** output=&primary[index];
    if (*output) Clear(index);
    RenderRect source={sx,sy,sx+sw,sy+sh};
    RenderRect target={dx,dy,dx+dw,dy+dh};
    RenderSurface* back;
    if (g_d3d_device->methods->GetBackBuffer(g_d3d_device,0,0,0,&back)!=0) return;
    RenderTargetMetadata* dimensions=&metadata[index];
    dimensions->width=dw;
    dimensions->height=dh;
    if (g_d3d_device->methods->CreateRenderTarget(g_d3d_device,dw,dh,g_render_target_format,0,0,1,output,0)==0 ||
        g_d3d_device->methods->CreatePlain(g_d3d_device,dimensions->width,dimensions->height,g_render_target_format,3,output,0)==0) {
        RenderSurface** other=&secondary[index];
        if (g_d3d_device->methods->CreatePlain(g_d3d_device,dimensions->width,dimensions->height,g_render_target_format,3,other,0)==0 &&
            CopySurface_004521d6(*output,0,&target,back,0,&source,0xffffffffU,0)==0)
            CopySurface_004521d6(*other,0,0,*output,0,0,0xffffffffU,0);
    }
    if (back) back->methods->Release(back);
}
#pragma code_seg()
