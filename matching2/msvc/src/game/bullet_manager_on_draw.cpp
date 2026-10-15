// 0x0040B060: the bullet manager's draw task; the bullets are drawn as
// animation objects, so it only reports success.
int __cdecl BulletManager_OnDraw() {
    return 1;
}
