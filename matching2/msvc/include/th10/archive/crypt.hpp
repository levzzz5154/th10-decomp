#ifndef TH10_ARCHIVE_CRYPT_HPP
#define TH10_ARCHIVE_CRYPT_HPP

// The byte cipher applied to th10.dat members, score files and replays.
//
// The buffer is handled in blocks. Within a block the plain bytes are read
// from the back in two interleaved passes - last, last-but-two, ..., then
// last-but-one, last-but-three, ... - and each is XORed with a rolling key
// that advances by `step` per byte and carries over into the next block.
//
// A final remainder shorter than a quarter block and the last byte of an
// odd-sized buffer are left as they are. `limit` bounds how much is
// transformed, in whole blocks. Both functions work in place and return
// `data`; they do nothing when the scratch copy cannot be allocated.
unsigned char* Dat_Decrypt(unsigned char* data, int size, unsigned char key,
                           unsigned char step, int block_size, int limit);
unsigned char* Dat_Encrypt(unsigned char* data, int size, unsigned char key,
                           unsigned char step, int block_size, int limit);

#endif
