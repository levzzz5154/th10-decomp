// padding: 0x004300CD..0x004300CF
// padding 004300cd..004300cf: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001155")
extern "C" unsigned char text_padding_004300cd[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x00430244..0x0043024F
// padding 00430244..0043024f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001156")
extern "C" unsigned char text_padding_00430244[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00430318..0x0043031F
// padding 00430318..0043031f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001157")
extern "C" unsigned char text_padding_00430318[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00430681..0x00430683
// padding 00430681..00430683: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001158")
extern "C" unsigned char text_padding_00430681[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// data: 0x00430684..0x00430697
// data 00430684..00430697: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001159")
extern "C" unsigned char text_data_00430684[] = {
    0x51, 0x03, 0x43, 0x00, 0xfd, 0x03, 0x43, 0x00, 0x23, 0x04, 0x43, 0x00, 0x9a, 0x05, 0x43, 0x00,
    0xfa, 0x05, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x00430698..0x0043069F
// padding 00430698..0043069f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001160")
extern "C" unsigned char text_padding_00430698[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// data: 0x00430A48..0x00430A5B
// data 00430a48..00430a5b: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001161")
extern "C" unsigned char text_data_00430a48[] = {
    0xbb, 0x06, 0x43, 0x00, 0xd4, 0x07, 0x43, 0x00, 0xf9, 0x07, 0x43, 0x00, 0x66, 0x09, 0x43, 0x00,
    0x00, 0x0a, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x00430A5C..0x00430A5F
// padding 00430a5c..00430a5f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001162")
extern "C" unsigned char text_padding_00430a5c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00430FDB..0x00430FDB
// padding 00430fdb..00430fdb: ["exact MSVC alignment NOP encoding (retail bytes are 0x90)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001163")
extern "C" unsigned char text_padding_00430fdb[] = {
    0x90,
};
#pragma data_seg()

// data: 0x00430FDC..0x00430FEF
// data 00430fdc..00430fef: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001164")
extern "C" unsigned char text_data_00430fdc[] = {
    0x7b, 0x0a, 0x43, 0x00, 0x3e, 0x0d, 0x43, 0x00, 0x63, 0x0d, 0x43, 0x00, 0x7d, 0x0e, 0x43, 0x00,
    0x95, 0x0f, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x004313F7..0x004313F7
// padding 004313f7..004313f7: ["exact MSVC alignment NOP encoding (retail bytes are 0x90)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001165")
extern "C" unsigned char text_padding_004313f7[] = {
    0x90,
};
#pragma data_seg()

// data: 0x004313F8..0x0043140B
// data 004313f8..0043140b: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001166")
extern "C" unsigned char text_data_004313f8[] = {
    0x0b, 0x10, 0x43, 0x00, 0x60, 0x10, 0x43, 0x00, 0x85, 0x10, 0x43, 0x00, 0x20, 0x13, 0x43, 0x00,
    0xb4, 0x13, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x0043140C..0x0043140F
// padding 0043140c..0043140f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001167")
extern "C" unsigned char text_padding_0043140c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004315B3..0x004315BF
// padding 004315b3..004315bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001168")
extern "C" unsigned char text_padding_004315b3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004316EA..0x004316EF
// padding 004316ea..004316ef: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D9B00000000)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001169")
extern "C" unsigned char text_padding_004316ea[] = {
    0x8d, 0x9b, 0x00, 0x00, 0x00, 0x00,
};
#pragma data_seg()

// padding: 0x00431B7A..0x00431B7B
// padding 00431b7a..00431b7b: ["exact MSVC alignment NOP encoding (retail bytes are 0x8BFF)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001170")
extern "C" unsigned char text_padding_00431b7a[] = {
    0x8b, 0xff,
};
#pragma data_seg()

// data: 0x00431B7C..0x00431B93
// data 00431b7c..00431b93: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001171")
extern "C" unsigned char text_data_00431b7c[] = {
    0xf2, 0x15, 0x43, 0x00, 0x4d, 0x17, 0x43, 0x00, 0xb1, 0x17, 0x43, 0x00, 0xb4, 0x19, 0x43, 0x00,
    0xfd, 0x18, 0x43, 0x00, 0x9e, 0x1a, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x00431B94..0x00431B9F
// padding 00431b94..00431b9f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001172")
extern "C" unsigned char text_padding_00431b94[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00431ED9..0x00431EDF
// padding 00431ed9..00431edf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001173")
extern "C" unsigned char text_padding_00431ed9[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043248D..0x0043248F
// padding 0043248d..0043248f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001174")
extern "C" unsigned char text_padding_0043248d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x0043267D..0x0043267F
// padding 0043267d..0043267f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001175")
extern "C" unsigned char text_padding_0043267d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// data: 0x00432680..0x0043268F
// data 00432680..0043268f: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001176")
extern "C" unsigned char text_data_00432680[] = {
    0x06, 0x1f, 0x43, 0x00, 0x95, 0x20, 0x43, 0x00, 0xba, 0x20, 0x43, 0x00, 0x15, 0x26, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x0043271D..0x0043271F
// padding 0043271d..0043271f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001177")
extern "C" unsigned char text_padding_0043271d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x0043298D..0x0043298F
// padding 0043298d..0043298f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001178")
extern "C" unsigned char text_padding_0043298d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x004329E2..0x004329EF
// padding 004329e2..004329ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001179")
extern "C" unsigned char text_padding_004329e2[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00432CA1..0x00432CAF
// padding 00432ca1..00432caf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001180")
extern "C" unsigned char text_padding_00432ca1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00433216..0x00433217
// padding 00433216..00433217: ["exact MSVC alignment NOP encoding (retail bytes are 0x8BFF)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001181")
extern "C" unsigned char text_padding_00433216[] = {
    0x8b, 0xff,
};
#pragma data_seg()

// data: 0x00433218..0x00433227
// data 00433218..00433227: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001182")
extern "C" unsigned char text_data_00433218[] = {
    0xcc, 0x2c, 0x43, 0x00, 0xda, 0x2e, 0x43, 0x00, 0x00, 0x2f, 0x43, 0x00, 0xac, 0x31, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x00433228..0x0043322F
// padding 00433228..0043322f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001183")
extern "C" unsigned char text_padding_00433228[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004333DD..0x004333DF
// padding 004333dd..004333df: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001184")
extern "C" unsigned char text_padding_004333dd[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x0043356A..0x0043356F
// padding 0043356a..0043356f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001185")
extern "C" unsigned char text_padding_0043356a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004335ED..0x004335EF
// padding 004335ed..004335ef: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001186")
extern "C" unsigned char text_padding_004335ed[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// data: 0x00433B10..0x00433B23
// data 00433b10..00433b23: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001187")
extern "C" unsigned char text_data_00433b10[] = {
    0x99, 0x35, 0x43, 0x00, 0x2f, 0x36, 0x43, 0x00, 0x4d, 0x36, 0x43, 0x00, 0xc9, 0x37, 0x43, 0x00,
    0x33, 0x3a, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x00433B24..0x00433B2F
// padding 00433b24..00433b2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001188")
extern "C" unsigned char text_padding_00433b24[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00433EEB..0x00433EEF
// padding 00433eeb..00433eef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001189")
extern "C" unsigned char text_padding_00433eeb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043408D..0x0043408F
// padding 0043408d..0043408f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001190")
extern "C" unsigned char text_padding_0043408d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x004349CA..0x004349CB
// padding 004349ca..004349cb: ["exact MSVC alignment NOP encoding (retail bytes are 0x8BFF)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001191")
extern "C" unsigned char text_padding_004349ca[] = {
    0x8b, 0xff,
};
#pragma data_seg()

// data: 0x004349CC..0x004349DB
// data 004349cc..004349db: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001192")
extern "C" unsigned char text_data_004349cc[] = {
    0x0e, 0x3f, 0x43, 0x00, 0x46, 0x43, 0x43, 0x00, 0x1b, 0x44, 0x43, 0x00, 0x4e, 0x49, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x004349DC..0x004349DF
// padding 004349dc..004349df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001193")
extern "C" unsigned char text_padding_004349dc[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434A1B..0x00434A1F
// padding 00434a1b..00434a1f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001194")
extern "C" unsigned char text_padding_00434a1b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434A7C..0x00434A7F
// padding 00434a7c..00434a7f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001195")
extern "C" unsigned char text_padding_00434a7c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434B4E..0x00434B4F
// padding 00434b4e..00434b4f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001196")
extern "C" unsigned char text_padding_00434b4e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434B64..0x00434B6F
// padding 00434b64..00434b6f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001197")
extern "C" unsigned char text_padding_00434b64[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434B7B..0x00434B7F
// padding 00434b7b..00434b7f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001198")
extern "C" unsigned char text_padding_00434b7b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434B8F..0x00434B8F
// padding 00434b8f..00434b8f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001199")
extern "C" unsigned char text_padding_00434b8f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x00434B95..0x00434B9F
// padding 00434b95..00434b9f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001200")
extern "C" unsigned char text_padding_00434b95[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434BB1..0x00434BBF
// padding 00434bb1..00434bbf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001201")
extern "C" unsigned char text_padding_00434bb1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434BD4..0x00434BDF
// padding 00434bd4..00434bdf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001202")
extern "C" unsigned char text_padding_00434bd4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434BE8..0x00434BEF
// padding 00434be8..00434bef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001203")
extern "C" unsigned char text_padding_00434be8[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434BFB..0x00434BFF
// padding 00434bfb..00434bff: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001204")
extern "C" unsigned char text_padding_00434bfb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434C01..0x00434C0F
// padding 00434c01..00434c0f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001205")
extern "C" unsigned char text_padding_00434c01[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434C2A..0x00434C2F
// padding 00434c2a..00434c2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001206")
extern "C" unsigned char text_padding_00434c2a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434C9C..0x00434C9F
// padding 00434c9c..00434c9f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001207")
extern "C" unsigned char text_padding_00434c9c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434D04..0x00434D0F
// padding 00434d04..00434d0f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001208")
extern "C" unsigned char text_padding_00434d04[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434D66..0x00434D6F
// padding 00434d66..00434d6f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001209")
extern "C" unsigned char text_padding_00434d66[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434DCD..0x00434DCF
// padding 00434dcd..00434dcf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001210")
extern "C" unsigned char text_padding_00434dcd[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434E5D..0x00434E5F
// padding 00434e5d..00434e5f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001211")
extern "C" unsigned char text_padding_00434e5d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x00434EE9..0x00434EEF
// padding 00434ee9..00434eef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001212")
extern "C" unsigned char text_padding_00434ee9[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434F23..0x00434F2F
// padding 00434f23..00434f2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001213")
extern "C" unsigned char text_padding_00434f23[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00434F65..0x00434F6F
// padding 00434f65..00434f6f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001214")
extern "C" unsigned char text_padding_00434f65[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004350CE..0x004350CF
// padding 004350ce..004350cf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001215")
extern "C" unsigned char text_padding_004350ce[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435217..0x0043521F
// padding 00435217..0043521f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001216")
extern "C" unsigned char text_padding_00435217[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043524F..0x0043524F
// padding 0043524f..0043524f: ["single INT3 separator immediately follows an authenticated RET/JMP at a function or basic-block boundary", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001217")
extern "C" unsigned char text_padding_0043524f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043526A..0x0043526F
// padding 0043526a..0043526f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001218")
extern "C" unsigned char text_padding_0043526a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043527C..0x0043527F
// padding 0043527c..0043527f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001219")
extern "C" unsigned char text_padding_0043527c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004352B3..0x004352BF
// padding 004352b3..004352bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001220")
extern "C" unsigned char text_padding_004352b3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004352C9..0x004352CF
// padding 004352c9..004352cf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001221")
extern "C" unsigned char text_padding_004352c9[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004352D1..0x004352DF
// padding 004352d1..004352df: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001222")
extern "C" unsigned char text_padding_004352d1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004352E1..0x004352EF
// padding 004352e1..004352ef: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001223")
extern "C" unsigned char text_padding_004352e1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004352F1..0x004352FF
// padding 004352f1..004352ff: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001224")
extern "C" unsigned char text_padding_004352f1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435315..0x0043531F
// padding 00435315..0043531f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001225")
extern "C" unsigned char text_padding_00435315[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043533E..0x0043533F
// padding 0043533e..0043533f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001226")
extern "C" unsigned char text_padding_0043533e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043536E..0x0043536F
// padding 0043536e..0043536f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001227")
extern "C" unsigned char text_padding_0043536e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004353AD..0x004353AF
// padding 004353ad..004353af: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001228")
extern "C" unsigned char text_padding_004353ad[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x0043545F..0x0043545F
// padding 0043545f..0043545f: ["single INT3 separator immediately follows an authenticated RET/JMP at a function or basic-block boundary", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001229")
extern "C" unsigned char text_padding_0043545f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x00435482..0x0043548F
// padding 00435482..0043548f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001230")
extern "C" unsigned char text_padding_00435482[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004354C9..0x004354CF
// padding 004354c9..004354cf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001231")
extern "C" unsigned char text_padding_004354c9[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043550F..0x0043550F
// padding 0043550f..0043550f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001232")
extern "C" unsigned char text_padding_0043550f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x00435529..0x0043552F
// padding 00435529..0043552f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001233")
extern "C" unsigned char text_padding_00435529[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435545..0x0043554F
// padding 00435545..0043554f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001234")
extern "C" unsigned char text_padding_00435545[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435575..0x0043557F
// padding 00435575..0043557f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001235")
extern "C" unsigned char text_padding_00435575[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435609..0x0043560F
// padding 00435609..0043560f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001236")
extern "C" unsigned char text_padding_00435609[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435689..0x0043568F
// padding 00435689..0043568f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001237")
extern "C" unsigned char text_padding_00435689[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435697..0x0043569F
// padding 00435697..0043569f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001238")
extern "C" unsigned char text_padding_00435697[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004356BF..0x004356BF
// padding 004356bf..004356bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001239")
extern "C" unsigned char text_padding_004356bf[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x004356C7..0x004356CF
// padding 004356c7..004356cf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001240")
extern "C" unsigned char text_padding_004356c7[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004356E4..0x004356EF
// padding 004356e4..004356ef: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001241")
extern "C" unsigned char text_padding_004356e4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043572D..0x0043572F
// padding 0043572d..0043572f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001242")
extern "C" unsigned char text_padding_0043572d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x004357C4..0x004357CF
// padding 004357c4..004357cf: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001243")
extern "C" unsigned char text_padding_004357c4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004357F4..0x004357FF
// padding 004357f4..004357ff: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001244")
extern "C" unsigned char text_padding_004357f4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004358D6..0x004358DF
// padding 004358d6..004358df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001245")
extern "C" unsigned char text_padding_004358d6[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043599E..0x0043599F
// padding 0043599e..0043599f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001246")
extern "C" unsigned char text_padding_0043599e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004359A4..0x004359AF
// padding 004359a4..004359af: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001247")
extern "C" unsigned char text_padding_004359a4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435B2D..0x00435B2F
// padding 00435b2d..00435b2f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001248")
extern "C" unsigned char text_padding_00435b2d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x00435DB5..0x00435DBF
// padding 00435db5..00435dbf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001249")
extern "C" unsigned char text_padding_00435db5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435F9B..0x00435F9F
// padding 00435f9b..00435f9f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001250")
extern "C" unsigned char text_padding_00435f9b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435FC4..0x00435FCF
// padding 00435fc4..00435fcf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001251")
extern "C" unsigned char text_padding_00435fc4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00435FFA..0x00435FFF
// padding 00435ffa..00435fff: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001252")
extern "C" unsigned char text_padding_00435ffa[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043601D..0x0043601F
// padding 0043601d..0043601f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001253")
extern "C" unsigned char text_padding_0043601d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x00436204..0x0043620F
// padding 00436204..0043620f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001254")
extern "C" unsigned char text_padding_00436204[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004362AF..0x004362AF
// padding 004362af..004362af: ["single INT3 separator immediately follows an authenticated RET/JMP at a function or basic-block boundary", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001255")
extern "C" unsigned char text_padding_004362af[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x00436325..0x0043632F
// padding 00436325..0043632f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001256")
extern "C" unsigned char text_padding_00436325[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043634A..0x0043634F
#pragma data_seg()

// padding: 0x00436361..0x0043636F
// padding 00436361..0043636f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001258")
extern "C" unsigned char text_padding_00436361[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436375..0x0043637F
// padding 00436375..0043637f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001259")
extern "C" unsigned char text_padding_00436375[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436392..0x0043639F
// padding 00436392..0043639f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001260")
extern "C" unsigned char text_padding_00436392[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004363BE..0x004363BF
// padding 004363be..004363bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001261")
extern "C" unsigned char text_padding_004363be[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004363F1..0x004363FF
// padding 004363f1..004363ff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001262")
extern "C" unsigned char text_padding_004363f1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043642E..0x0043642F
// padding 0043642e..0043642f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001263")
extern "C" unsigned char text_padding_0043642e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436455..0x0043645F
// padding 00436455..0043645f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001264")
extern "C" unsigned char text_padding_00436455[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004364CC..0x004364CF
// padding 004364cc..004364cf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001265")
extern "C" unsigned char text_padding_004364cc[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004364D7..0x004364DF
// padding 004364d7..004364df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001266")
extern "C" unsigned char text_padding_004364d7[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004364E4..0x004364EF
// padding 004364e4..004364ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001267")
extern "C" unsigned char text_padding_004364e4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043655B..0x0043655F
// padding 0043655b..0043655f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001268")
extern "C" unsigned char text_padding_0043655b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436569..0x0043656F
// padding 00436569..0043656f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001269")
extern "C" unsigned char text_padding_00436569[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436639..0x0043663F
// padding 00436639..0043663f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001270")
extern "C" unsigned char text_padding_00436639[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436652..0x0043665F
// padding 00436652..0043665f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001271")
extern "C" unsigned char text_padding_00436652[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043667E..0x0043667F
// padding 0043667e..0043667f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001272")
extern "C" unsigned char text_padding_0043667e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004366B1..0x004366BF
// padding 004366b1..004366bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001273")
extern "C" unsigned char text_padding_004366b1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436768..0x0043676F
// padding 00436768..0043676f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001274")
extern "C" unsigned char text_padding_00436768[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043677D..0x0043677F
// padding 0043677d..0043677f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001275")
extern "C" unsigned char text_padding_0043677d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436791..0x0043679F
// padding 00436791..0043679f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001276")
extern "C" unsigned char text_padding_00436791[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004367C3..0x004367CF
// padding 004367c3..004367cf: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001277")
extern "C" unsigned char text_padding_004367c3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004367D5..0x004367DF
// padding 004367d5..004367df: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001278")
extern "C" unsigned char text_padding_004367d5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004367EB..0x004367EF
// padding 004367eb..004367ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001279")
extern "C" unsigned char text_padding_004367eb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004367F3..0x004367FF
// padding 004367f3..004367ff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001280")
extern "C" unsigned char text_padding_004367f3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436807..0x0043680F
// padding 00436807..0043680f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001281")
extern "C" unsigned char text_padding_00436807[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436817..0x0043681F
// padding 00436817..0043681f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001282")
extern "C" unsigned char text_padding_00436817[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436827..0x0043682F
// padding 00436827..0043682f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001283")
extern "C" unsigned char text_padding_00436827[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436837..0x0043683F
// padding 00436837..0043683f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001284")
extern "C" unsigned char text_padding_00436837[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436847..0x0043684F
// padding 00436847..0043684f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001285")
extern "C" unsigned char text_padding_00436847[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436857..0x0043685F
// padding 00436857..0043685f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001286")
extern "C" unsigned char text_padding_00436857[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043686E..0x0043686F
// padding 0043686e..0043686f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001287")
extern "C" unsigned char text_padding_0043686e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043688F..0x0043688F
// padding 0043688f..0043688f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001288")
extern "C" unsigned char text_padding_0043688f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x004368F3..0x004368FF
// padding 004368f3..004368ff: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001289")
extern "C" unsigned char text_padding_004368f3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436938..0x0043693F
// padding 00436938..0043693f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001290")
extern "C" unsigned char text_padding_00436938[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436961..0x0043696F
// padding 00436961..0043696f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001291")
extern "C" unsigned char text_padding_00436961[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004369BB..0x004369BF
// padding 004369bb..004369bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001292")
extern "C" unsigned char text_padding_004369bb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004369D4..0x004369DF
// padding 004369d4..004369df: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001293")
extern "C" unsigned char text_padding_004369d4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436A11..0x00436A1F
// padding 00436a11..00436a1f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001294")
extern "C" unsigned char text_padding_00436a11[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436A25..0x00436A2F
// padding 00436a25..00436a2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001295")
extern "C" unsigned char text_padding_00436a25[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436A9B..0x00436A9F
// padding 00436a9b..00436a9f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001296")
extern "C" unsigned char text_padding_00436a9b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436AEC..0x00436AEF
// padding 00436aec..00436aef: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001297")
extern "C" unsigned char text_padding_00436aec[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436C95..0x00436C9F
// padding 00436c95..00436c9f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001298")
extern "C" unsigned char text_padding_00436c95[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436CE8..0x00436CEF
// padding 00436ce8..00436cef: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001299")
extern "C" unsigned char text_padding_00436ce8[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436D27..0x00436D2F
// padding 00436d27..00436d2f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001300")
extern "C" unsigned char text_padding_00436d27[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436D5E..0x00436D5F
// padding 00436d5e..00436d5f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001301")
extern "C" unsigned char text_padding_00436d5e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00436D97..0x00436D9F
// padding 00436d97..00436d9f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001302")
extern "C" unsigned char text_padding_00436d97[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00437152..0x0043715F
// padding 00437152..0043715f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001303")
extern "C" unsigned char text_padding_00437152[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004371FD..0x004371FF
// padding 004371fd..004371ff: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001304")
extern "C" unsigned char text_padding_004371fd[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043729F..0x0043729F
// padding 0043729f..0043729f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001305")
extern "C" unsigned char text_padding_0043729f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043737E..0x0043737F
// padding 0043737e..0043737f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001306")
extern "C" unsigned char text_padding_0043737e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043758D..0x0043758F
// padding 0043758d..0043758f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001307")
extern "C" unsigned char text_padding_0043758d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00437666..0x0043766F
// padding 00437666..0043766f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001308")
extern "C" unsigned char text_padding_00437666[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00437746..0x0043774F
// padding 00437746..0043774f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001309")
extern "C" unsigned char text_padding_00437746[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004379D5..0x004379DF
// padding 004379d5..004379df: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001310")
extern "C" unsigned char text_padding_004379d5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004379FF..0x004379FF
// padding 004379ff..004379ff: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001311")
extern "C" unsigned char text_padding_004379ff[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x00437D0D..0x00437D0F
// padding 00437d0d..00437d0f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001312")
extern "C" unsigned char text_padding_00437d0d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00437DA5..0x00437DAF
// padding 00437da5..00437daf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001313")
extern "C" unsigned char text_padding_00437da5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00437FDA..0x00437FDF
// padding 00437fda..00437fdf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001314")
extern "C" unsigned char text_padding_00437fda[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004381DD..0x004381DF
// padding 004381dd..004381df: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001315")
extern "C" unsigned char text_padding_004381dd[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438216..0x0043821F
// padding 00438216..0043821f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001316")
extern "C" unsigned char text_padding_00438216[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043823E..0x0043823F
// padding 0043823e..0043823f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001317")
extern "C" unsigned char text_padding_0043823e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043824E..0x0043824F
// padding 0043824e..0043824f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001318")
extern "C" unsigned char text_padding_0043824e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438254..0x0043825F
// padding 00438254..0043825f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001319")
extern "C" unsigned char text_padding_00438254[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438343..0x0043834F
// padding 00438343..0043834f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001320")
extern "C" unsigned char text_padding_00438343[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438375..0x0043837F
// padding 00438375..0043837f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001322")
extern "C" unsigned char text_padding_00438375[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004383D3..0x004383DF
// padding 004383d3..004383df: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001323")
extern "C" unsigned char text_padding_004383d3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004383EE..0x004383EF
// padding 004383ee..004383ef: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001324")
extern "C" unsigned char text_padding_004383ee[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004383F5..0x004383FF
// padding 004383f5..004383ff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001325")
extern "C" unsigned char text_padding_004383f5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438403..0x0043840F
// padding 00438403..0043840f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001326")
extern "C" unsigned char text_padding_00438403[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438415..0x0043841F
// padding 00438415..0043841f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001327")
extern "C" unsigned char text_padding_00438415[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043850A..0x0043850F
// padding 0043850a..0043850f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001328")
extern "C" unsigned char text_padding_0043850a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438585..0x0043858F
// padding 00438585..0043858f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001329")
extern "C" unsigned char text_padding_00438585[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004385AF..0x004385AF
// padding 004385af..004385af: ["single INT3 separator immediately follows an authenticated RET/JMP at a function or basic-block boundary", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001330")
extern "C" unsigned char text_padding_004385af[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043867A..0x0043867F
// padding 0043867a..0043867f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001331")
extern "C" unsigned char text_padding_0043867a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043868E..0x0043868F
// padding 0043868e..0043868f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001332")
extern "C" unsigned char text_padding_0043868e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043869E..0x0043869F
// padding 0043869e..0043869f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001333")
extern "C" unsigned char text_padding_0043869e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004386A6..0x004386AF
// padding 004386a6..004386af: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001334")
extern "C" unsigned char text_padding_004386a6[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004387F2..0x004387FF
// Padding after the compiler-generated Grow catch-all trap.
#pragma data_seg(".d001335")
extern "C" unsigned char text_padding_004387f3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438839..0x0043883F
// padding 00438839..0043883f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001336")
extern "C" unsigned char text_padding_00438839[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438854..0x0043885F
// padding 00438854..0043885f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001337")
extern "C" unsigned char text_padding_00438854[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043886A..0x0043886F
// padding 0043886a..0043886f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001338")
extern "C" unsigned char text_padding_0043886a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438871..0x0043887F
// padding 00438871..0043887f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001339")
extern "C" unsigned char text_padding_00438871[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004388E7..0x004388EF
// padding 004388e7..004388ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001340")
extern "C" unsigned char text_padding_004388e7[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438906..0x0043890F
// padding 00438906..0043890f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001341")
extern "C" unsigned char text_padding_00438906[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043893B..0x0043893F
// padding 0043893b..0043893f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001342")
extern "C" unsigned char text_padding_0043893b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043894A..0x0043894F
// padding 0043894a..0043894f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001343")
extern "C" unsigned char text_padding_0043894a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043899F..0x0043899F
// padding 0043899f..0043899f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001344")
extern "C" unsigned char text_padding_0043899f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x004389B3..0x004389BF
// padding 004389b3..004389bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001345")
extern "C" unsigned char text_padding_004389b3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004389C4..0x004389CF
// padding 004389c4..004389cf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001346")
extern "C" unsigned char text_padding_004389c4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004389D4..0x004389DF
// padding 004389d4..004389df: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001347")
extern "C" unsigned char text_padding_004389d4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004389E4..0x004389EF
// padding 004389e4..004389ef: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001348")
extern "C" unsigned char text_padding_004389e4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438A05..0x00438A0F
// padding 00438a05..00438a0f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001349")
extern "C" unsigned char text_padding_00438a05[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438A25..0x00438A2F
// padding 00438a25..00438a2f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001350")
extern "C" unsigned char text_padding_00438a25[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00438A5B..0x00438A5F
// padding 00438a5b..00438a5f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001351")
extern "C" unsigned char text_padding_00438a5b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043900D..0x0043900F
// padding 0043900d..0043900f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001352")
extern "C" unsigned char text_padding_0043900d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x0043903D..0x0043903F
// padding 0043903d..0043903f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001353")
extern "C" unsigned char text_padding_0043903d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043905B..0x0043905F
// padding 0043905b..0043905f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001354")
extern "C" unsigned char text_padding_0043905b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043907B..0x0043907F
// padding 0043907b..0043907f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001355")
extern "C" unsigned char text_padding_0043907b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043909C..0x0043909F
// padding 0043909c..0043909f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001356")
extern "C" unsigned char text_padding_0043909c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004390DF..0x004390DF
// padding 004390df..004390df: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001357")
extern "C" unsigned char text_padding_004390df[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x004391E9..0x004391EF
// padding 004391e9..004391ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001358")
extern "C" unsigned char text_padding_004391e9[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00439344..0x0043934F
// padding 00439344..0043934f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001359")
extern "C" unsigned char text_padding_00439344[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043938E..0x0043938F
// padding 0043938e..0043938f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001360")
extern "C" unsigned char text_padding_0043938e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00439539..0x0043953F
// padding 00439539..0043953f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001361")
extern "C" unsigned char text_padding_00439539[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043965A..0x0043965F
// padding 0043965a..0043965f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001362")
extern "C" unsigned char text_padding_0043965a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x004396F8..0x004396FF
// padding 004396f8..004396ff: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001363")
extern "C" unsigned char text_padding_004396f8[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043972D..0x0043972F
// padding 0043972d..0043972f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001364")
extern "C" unsigned char text_padding_0043972d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00439885..0x0043988F
// padding 00439885..0043988f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001365")
extern "C" unsigned char text_padding_00439885[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00439D17..0x00439D1F
// padding 00439d17..00439d1f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001366")
extern "C" unsigned char text_padding_00439d17[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x00439FE6..0x00439FEF
// padding 00439fe6..00439fef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001367")
extern "C" unsigned char text_padding_00439fe6[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A11D..0x0043A11F
// padding 0043a11d..0043a11f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001368")
extern "C" unsigned char text_padding_0043a11d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x0043A1AA..0x0043A1AF
// padding 0043a1aa..0043a1af: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001369")
extern "C" unsigned char text_padding_0043a1aa[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A1B8..0x0043A1BF
// padding 0043a1b8..0043a1bf: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001370")
extern "C" unsigned char text_padding_0043a1b8[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A28F..0x0043A28F
// padding 0043a28f..0043a28f: ["single INT3 separator immediately follows an authenticated RET/JMP at a function or basic-block boundary", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001371")
extern "C" unsigned char text_padding_0043a28f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043A489..0x0043A48F
// padding 0043a489..0043a48f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001372")
extern "C" unsigned char text_padding_0043a489[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A49E..0x0043A49F
// padding 0043a49e..0043a49f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001373")
extern "C" unsigned char text_padding_0043a49e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A4BD..0x0043A4BF
// padding 0043a4bd..0043a4bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001374")
extern "C" unsigned char text_padding_0043a4bd[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A504..0x0043A50F
// padding 0043a504..0043a50f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001375")
extern "C" unsigned char text_padding_0043a504[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A533..0x0043A53F
// padding 0043a533..0043a53f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001376")
extern "C" unsigned char text_padding_0043a533[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A56E..0x0043A56F
// padding 0043a56e..0043a56f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001377")
extern "C" unsigned char text_padding_0043a56e[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A586..0x0043A58F
// padding 0043a586..0043a58f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001378")
extern "C" unsigned char text_padding_0043a586[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A5BF..0x0043A5BF
// padding 0043a5bf..0043a5bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001379")
extern "C" unsigned char text_padding_0043a5bf[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043A5FF..0x0043A5FF
// padding 0043a5ff..0043a5ff: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001380")
extern "C" unsigned char text_padding_0043a5ff[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043A61C..0x0043A61F
// padding 0043a61c..0043a61f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001381")
extern "C" unsigned char text_padding_0043a61c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A6AD..0x0043A6AF
// padding 0043a6ad..0043a6af: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001382")
extern "C" unsigned char text_padding_0043a6ad[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A6D5..0x0043A6DF
// padding 0043a6d5..0043a6df: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001383")
extern "C" unsigned char text_padding_0043a6d5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A6EB..0x0043A6EF
// padding 0043a6eb..0043a6ef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001384")
extern "C" unsigned char text_padding_0043a6eb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A6FE..0x0043A6FF
// padding 0043a6fe..0043a6ff: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001385")
extern "C" unsigned char text_padding_0043a6fe[] = {
    0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A725..0x0043A72F
// padding 0043a725..0043a72f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001386")
extern "C" unsigned char text_padding_0043a725[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A74A..0x0043A74F
// padding 0043a74a..0043a74f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001387")
extern "C" unsigned char text_padding_0043a74a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A904..0x0043A90F
// padding 0043a904..0043a90f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001388")
extern "C" unsigned char text_padding_0043a904[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043A9AC..0x0043A9AF
// padding 0043a9ac..0043a9af: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001389")
extern "C" unsigned char text_padding_0043a9ac[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043AA24..0x0043AA2F
// padding 0043aa24..0043aa2f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001390")
extern "C" unsigned char text_padding_0043aa24[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043AA5B..0x0043AA5F
// padding 0043aa5b..0043aa5f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001391")
extern "C" unsigned char text_padding_0043aa5b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043AACB..0x0043AACF
// padding 0043aacb..0043aacf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001392")
extern "C" unsigned char text_padding_0043aacb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043ACD8..0x0043ACDF
// padding 0043acd8..0043acdf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001393")
extern "C" unsigned char text_padding_0043acd8[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043AD64..0x0043AD6F
// padding 0043ad64..0043ad6f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001394")
extern "C" unsigned char text_padding_0043ad64[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043AE17..0x0043AE1F
// padding 0043ae17..0043ae1f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001395")
extern "C" unsigned char text_padding_0043ae17[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043AEA1..0x0043AEAF
// padding 0043aea1..0043aeaf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001396")
extern "C" unsigned char text_padding_0043aea1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043AEFF..0x0043AEFF
// padding 0043aeff..0043aeff: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001397")
extern "C" unsigned char text_padding_0043aeff[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043AF27..0x0043AF2F
// padding 0043af27..0043af2f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001398")
extern "C" unsigned char text_padding_0043af27[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043B02A..0x0043B02F
// padding 0043b02a..0043b02f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D9B00000000)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001399")
extern "C" unsigned char text_padding_0043b02a[] = {
    0x8d, 0x9b, 0x00, 0x00, 0x00, 0x00,
};
#pragma data_seg()

// padding: 0x0043B109..0x0043B10F
// padding 0043b109..0043b10f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001400")
extern "C" unsigned char text_padding_0043b109[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043B63B..0x0043B63B
// padding 0043b63b..0043b63b: ["exact MSVC alignment NOP encoding (retail bytes are 0x90)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001401")
extern "C" unsigned char text_padding_0043b63b[] = {
    0x90,
};
#pragma data_seg()

// data: 0x0043B63C..0x0043B795
// data 0043b63c..0043b647: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001402")
extern "C" unsigned char text_data_0043b63c[] = {
    0x8d, 0xb3, 0x43, 0x00, 0xa6, 0xb3, 0x43, 0x00, 0x78, 0xb1, 0x43, 0x00, 0x87, 0xb2, 0x43, 0x00,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x02, 0x8d, 0x49, 0x00, 0xee, 0xb3, 0x43, 0x00, 0xbb, 0xb3, 0x43, 0x00, 0x31, 0xb4, 0x43, 0x00,
    0x1f, 0xb4, 0x43, 0x00, 0xd8, 0xb5, 0x43, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x8d, 0x49, 0x00, 0x4b, 0xb4, 0x43, 0x00,
    0x02, 0xb5, 0x43, 0x00, 0x6e, 0xb5, 0x43, 0x00, 0x61, 0xb4, 0x43, 0x00, 0xec, 0xb4, 0x43, 0x00,
    0xc0, 0xb4, 0x43, 0x00, 0xd6, 0xb4, 0x43, 0x00, 0xd8, 0xb5, 0x43, 0x00, 0x00, 0x07, 0x01, 0x07,
    0x02, 0x07, 0x07, 0x03, 0x07, 0x07, 0x04, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x05, 0x07, 0x06,
};
#pragma data_seg()

// padding: 0x0043B796..0x0043B79F
// padding 0043b796..0043b79f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001403")
extern "C" unsigned char text_padding_0043b796[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043B82C..0x0043B82F
// padding 0043b82c..0043b82f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001404")
extern "C" unsigned char text_padding_0043b82c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043B83C..0x0043B83F
// padding 0043b83c..0043b83f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001405")
extern "C" unsigned char text_padding_0043b83c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043B881..0x0043B88F
// padding 0043b881..0043b88f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001406")
extern "C" unsigned char text_padding_0043b881[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043B8B1..0x0043B8BF
// padding 0043b8b1..0043b8bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001407")
extern "C" unsigned char text_padding_0043b8b1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043B8C1..0x0043B8CF
// padding 0043b8c1..0043b8cf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001408")
extern "C" unsigned char text_padding_0043b8c1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BA87..0x0043BA8F
// padding 0043ba87..0043ba8f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001409")
extern "C" unsigned char text_padding_0043ba87[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BAE3..0x0043BAEF
// padding 0043bae3..0043baef: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001410")
extern "C" unsigned char text_padding_0043bae3[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BB24..0x0043BB2F
// padding 0043bb24..0043bb2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001411")
extern "C" unsigned char text_padding_0043bb24[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BB92..0x0043BB9F
// padding 0043bb92..0043bb9f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001412")
extern "C" unsigned char text_padding_0043bb92[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BBED..0x0043BBEF
// padding 0043bbed..0043bbef: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001413")
extern "C" unsigned char text_padding_0043bbed[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BBF4..0x0043BBFF
// padding 0043bbf4..0043bbff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001414")
extern "C" unsigned char text_padding_0043bbf4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BC04..0x0043BC0F
// padding 0043bc04..0043bc0f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001415")
extern "C" unsigned char text_padding_0043bc04[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BC14..0x0043BC1F
// padding 0043bc14..0043bc1f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001416")
extern "C" unsigned char text_padding_0043bc14[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BC37..0x0043BC3F
// padding 0043bc37..0043bc3f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001417")
extern "C" unsigned char text_padding_0043bc37[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BCC7..0x0043BCCF
// padding 0043bcc7..0043bccf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001418")
extern "C" unsigned char text_padding_0043bcc7[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BD3C..0x0043BD3F
// padding 0043bd3c..0043bd3f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001419")
extern "C" unsigned char text_padding_0043bd3c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BD9D..0x0043BD9F
// padding 0043bd9d..0043bd9f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001420")
extern "C" unsigned char text_padding_0043bd9d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BF83..0x0043BF8F
// padding 0043bf83..0043bf8f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001421")
extern "C" unsigned char text_padding_0043bf83[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043BF93..0x0043BF9F
// padding 0043bf93..0043bf9f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001422")
extern "C" unsigned char text_padding_0043bf93[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C195..0x0043C19F
// padding 0043c195..0043c19f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001423")
extern "C" unsigned char text_padding_0043c195[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C226..0x0043C22F
// padding 0043c226..0043c22f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001424")
extern "C" unsigned char text_padding_0043c226[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C2B5..0x0043C2BF
// padding 0043c2b5..0043c2bf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001425")
extern "C" unsigned char text_padding_0043c2b5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C304..0x0043C30F
// padding 0043c304..0043c30f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001426")
extern "C" unsigned char text_padding_0043c304[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C3BF..0x0043C3BF
// padding 0043c3bf..0043c3bf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001427")
extern "C" unsigned char text_padding_0043c3bf[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043C404..0x0043C40F
// padding 0043c404..0043c40f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001428")
extern "C" unsigned char text_padding_0043c404[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C454..0x0043C45F
// padding 0043c454..0043c45f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001429")
extern "C" unsigned char text_padding_0043c454[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C4FA..0x0043C4FF
// padding 0043c4fa..0043c4ff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001430")
extern "C" unsigned char text_padding_0043c4fa[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C54A..0x0043C54F
// padding 0043c54a..0043c54f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001431")
extern "C" unsigned char text_padding_0043c54a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C707..0x0043C70F
// padding 0043c707..0043c70f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001432")
extern "C" unsigned char text_padding_0043c707[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C86D..0x0043C86F
// padding 0043c86d..0043c86f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001433")
extern "C" unsigned char text_padding_0043c86d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C88A..0x0043C88F
// padding 0043c88a..0043c88f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001434")
extern "C" unsigned char text_padding_0043c88a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C8AB..0x0043C8AF
// padding 0043c8ab..0043c8af: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001435")
extern "C" unsigned char text_padding_0043c8ab[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C902..0x0043C90F
// padding 0043c902..0043c90f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001436")
extern "C" unsigned char text_padding_0043c902[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C922..0x0043C92F
// padding 0043c922..0043c92f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001437")
extern "C" unsigned char text_padding_0043c922[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043C969..0x0043C96F
// padding 0043c969..0043c96f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001438")
extern "C" unsigned char text_padding_0043c969[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043CAD5..0x0043CAD7
// padding 0043cad5..0043cad7: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001439")
extern "C" unsigned char text_padding_0043cad5[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// data: 0x0043CAD8..0x0043CAFB
// data 0043cad8..0043cafb: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001440")
extern "C" unsigned char text_data_0043cad8[] = {
    0x86, 0xc9, 0x43, 0x00, 0xae, 0xc9, 0x43, 0x00, 0xb8, 0xc9, 0x43, 0x00, 0xe0, 0xc9, 0x43, 0x00,
    0xf5, 0xc9, 0x43, 0x00, 0xee, 0xc9, 0x43, 0x00, 0x1a, 0xca, 0x43, 0x00, 0x3f, 0xca, 0x43, 0x00,
    0x64, 0xca, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x0043CAFC..0x0043CAFF
// padding 0043cafc..0043caff: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001441")
extern "C" unsigned char text_padding_0043cafc[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043CB7F..0x0043CB7F
// padding 0043cb7f..0043cb7f: ["single INT3 separator immediately follows an authenticated RET/JMP at a function or basic-block boundary", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001442")
extern "C" unsigned char text_padding_0043cb7f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043CBD8..0x0043CBDF
// padding 0043cbd8..0043cbdf: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001443")
extern "C" unsigned char text_padding_0043cbd8[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043CBE1..0x0043CBEF
// padding 0043cbe1..0043cbef: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001444")
extern "C" unsigned char text_padding_0043cbe1[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043CC2B..0x0043CC2F
// padding 0043cc2b..0043cc2f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001445")
extern "C" unsigned char text_padding_0043cc2b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043CC3D..0x0043CC3F
// padding 0043cc3d..0043cc3f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001446")
extern "C" unsigned char text_padding_0043cc3d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043CCEF..0x0043CCEF
// padding 0043ccef..0043ccef: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001447")
extern "C" unsigned char text_padding_0043ccef[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043CD29..0x0043CD2F
// padding 0043cd29..0043cd2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001448")
extern "C" unsigned char text_padding_0043cd29[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D042..0x0043D04F
// padding 0043d042..0043d04f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001449")
extern "C" unsigned char text_padding_0043d042[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D077..0x0043D07F
// padding 0043d077..0043d07f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001450")
extern "C" unsigned char text_padding_0043d077[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D0EB..0x0043D0EF
// padding 0043d0eb..0043d0ef: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001451")
extern "C" unsigned char text_padding_0043d0eb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D112..0x0043D11F
// padding 0043d112..0043d11f: ["live Ghidra disassembly identified INT3/NOP bytes inside a missed-code candidate range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001452")
extern "C" unsigned char text_padding_0043d112[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D24D..0x0043D24F
// padding 0043d24d..0043d24f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001453")
extern "C" unsigned char text_padding_0043d24d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D297..0x0043D29F
// padding 0043d297..0043d29f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001454")
extern "C" unsigned char text_padding_0043d297[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D383..0x0043D38F
// padding 0043d383..0043d38f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001455")
extern "C" unsigned char text_padding_0043d383[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D63C..0x0043D63F
// padding 0043d63c..0043d63f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001456")
extern "C" unsigned char text_padding_0043d63c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D665..0x0043D66F
// padding 0043d665..0043d66f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001457")
extern "C" unsigned char text_padding_0043d665[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D781..0x0043D78F
// padding 0043d781..0043d78f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001458")
extern "C" unsigned char text_padding_0043d781[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D7C7..0x0043D7CF
// padding 0043d7c7..0043d7cf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001459")
extern "C" unsigned char text_padding_0043d7c7[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043D941..0x0043D94F
// padding 0043d941..0043d94f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001460")
extern "C" unsigned char text_padding_0043d941[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043DA7A..0x0043DA7F
// padding 0043da7a..0043da7f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001461")
extern "C" unsigned char text_padding_0043da7a[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043DAAC..0x0043DAAF
// padding 0043daac..0043daaf: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001462")
extern "C" unsigned char text_padding_0043daac[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043DC87..0x0043DC8F
// padding 0043dc87..0043dc8f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001463")
extern "C" unsigned char text_padding_0043dc87[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043DD0B..0x0043DD0F
// padding 0043dd0b..0043dd0f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001464")
extern "C" unsigned char text_padding_0043dd0b[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043DDA5..0x0043DDAF
// padding 0043dda5..0043ddaf: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001465")
extern "C" unsigned char text_padding_0043dda5[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043DDE4..0x0043DDEF
// padding 0043dde4..0043ddef: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001466")
extern "C" unsigned char text_padding_0043dde4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E37B..0x0043E37B
// padding 0043e37b..0043e37b: ["exact MSVC alignment NOP encoding (retail bytes are 0x90)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001467")
extern "C" unsigned char text_padding_0043e37b[] = {
    0x90,
};
#pragma data_seg()

// data: 0x0043E37C..0x0043E39B
// data 0043e37c..0043e39b: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001468")
extern "C" unsigned char text_data_0043e37c[] = {
    0x64, 0xde, 0x43, 0x00, 0xab, 0xde, 0x43, 0x00, 0x53, 0xe0, 0x43, 0x00, 0xf0, 0xdf, 0x43, 0x00,
    0x76, 0xe0, 0x43, 0x00, 0x99, 0xe0, 0x43, 0x00, 0xbe, 0xe0, 0x43, 0x00, 0x45, 0xde, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x0043E39C..0x0043E39F
// padding 0043e39c..0043e39f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001469")
extern "C" unsigned char text_padding_0043e39c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E45D..0x0043E45F
// padding 0043e45d..0043e45f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001470")
extern "C" unsigned char text_padding_0043e45d[] = {
    0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E46D..0x0043E46F
// padding 0043e46d..0043e46f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8D4900)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001471")
extern "C" unsigned char text_padding_0043e46d[] = {
    0x8d, 0x49, 0x00,
};
#pragma data_seg()

// padding: 0x0043E4C8..0x0043E4CF
// padding 0043e4c8..0043e4cf: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001472")
extern "C" unsigned char text_padding_0043e4c8[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E4FB..0x0043E4FF
// padding 0043e4fb..0043e4ff: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001473")
extern "C" unsigned char text_padding_0043e4fb[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E51F..0x0043E51F
// padding 0043e51f..0043e51f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001474")
extern "C" unsigned char text_padding_0043e51f[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043E527..0x0043E52F
// padding 0043e527..0043e52f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001475")
extern "C" unsigned char text_padding_0043e527[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E534..0x0043E53F
// padding 0043e534..0043e53f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001476")
extern "C" unsigned char text_padding_0043e534[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E563..0x0043E56F
// padding 0043e563..0043e56f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001477")
extern "C" unsigned char text_padding_0043e563[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E571..0x0043E57F
// padding 0043e571..0043e57f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001478")
extern "C" unsigned char text_padding_0043e571[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E704..0x0043E70F
// padding 0043e704..0043e70f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001479")
extern "C" unsigned char text_padding_0043e704[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E7DB..0x0043E7DF
// padding 0043e7db..0043e7df: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001480")
extern "C" unsigned char text_padding_0043e7db[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E8A2..0x0043E8AF
// padding 0043e8a2..0043e8af: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001481")
extern "C" unsigned char text_padding_0043e8a2[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043E9CF..0x0043E9CF
// padding 0043e9cf..0043e9cf: ["single INT3 separator immediately follows an authenticated RET/JMP at a function or basic-block boundary", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001482")
extern "C" unsigned char text_padding_0043e9cf[] = {
    0xcc,
};
#pragma data_seg()

// padding: 0x0043EA5F..0x0043EA5F
// padding 0043ea5f..0043ea5f: ["live Ghidra disassembly identified INT3/NOP bytes inside an unresolved range", "retail bytes retained verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001483")
extern "C" unsigned char text_padding_0043ea5f[] = {
    0x90,
};
#pragma data_seg()

// padding: 0x0043EAB4..0x0043EABF
// padding 0043eab4..0043eabf: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001484")
extern "C" unsigned char text_padding_0043eab4[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// padding: 0x0043EC0E..0x0043EC0F
// padding 0043ec0e..0043ec0f: ["exact MSVC alignment NOP encoding (retail bytes are 0x8BFF)", "neighboring authenticated control flow is an unconditional JMP or RET, so the span is unreachable padding", "retail bytes are preserved verbatim; candidate is not promoted to instruction"]
#pragma data_seg(".d001485")
extern "C" unsigned char text_padding_0043ec0e[] = {
    0x8b, 0xff,
};
#pragma data_seg()

// data: 0x0043EC10..0x0043EC67
// data 0043ec10..0043ec67: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001486")
extern "C" unsigned char text_data_0043ec10[] = {
    0xde, 0xea, 0x43, 0x00, 0xe7, 0xea, 0x43, 0x00, 0xf0, 0xea, 0x43, 0x00, 0xf9, 0xea, 0x43, 0x00,
    0x02, 0xeb, 0x43, 0x00, 0x0b, 0xeb, 0x43, 0x00, 0x14, 0xeb, 0x43, 0x00, 0x1d, 0xeb, 0x43, 0x00,
    0x26, 0xeb, 0x43, 0x00, 0x2f, 0xeb, 0x43, 0x00, 0x84, 0xeb, 0x43, 0x00, 0x38, 0xeb, 0x43, 0x00,
    0x5e, 0xeb, 0x43, 0x00, 0xb6, 0xeb, 0x43, 0x00, 0xbf, 0xeb, 0x43, 0x00, 0xc8, 0xeb, 0x43, 0x00,
    0xd1, 0xeb, 0x43, 0x00, 0xda, 0xeb, 0x43, 0x00, 0xe3, 0xeb, 0x43, 0x00, 0xec, 0xeb, 0x43, 0x00,
    0xf5, 0xeb, 0x43, 0x00, 0xfe, 0xeb, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x0043EC68..0x0043EC6F
// padding 0043ec68..0043ec6f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001487")
extern "C" unsigned char text_padding_0043ec68[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// data: 0x0043ECD8..0x0043ECFF
// data 0043ecd8..0043ecff: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001488")
extern "C" unsigned char text_data_0043ecd8[] = {
    0x82, 0xec, 0x43, 0x00, 0x89, 0xec, 0x43, 0x00, 0x90, 0xec, 0x43, 0x00, 0x97, 0xec, 0x43, 0x00,
    0x9e, 0xec, 0x43, 0x00, 0xa9, 0xec, 0x43, 0x00, 0xb4, 0xec, 0x43, 0x00, 0xbf, 0xec, 0x43, 0x00,
    0xca, 0xec, 0x43, 0x00, 0xd1, 0xec, 0x43, 0x00,
};
#pragma data_seg()

// data: 0x0043ED6C..0x0043ED9B
// data 0043ed6c..0043ed9b: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001489")
extern "C" unsigned char text_data_0043ed6c[] = {
    0x28, 0xed, 0x43, 0x00, 0x31, 0xed, 0x43, 0x00, 0x3a, 0xed, 0x43, 0x00, 0x43, 0xed, 0x43, 0x00,
    0x67, 0xed, 0x43, 0x00, 0x67, 0xed, 0x43, 0x00, 0x67, 0xed, 0x43, 0x00, 0x67, 0xed, 0x43, 0x00,
    0x67, 0xed, 0x43, 0x00, 0x4c, 0xed, 0x43, 0x00, 0x55, 0xed, 0x43, 0x00, 0x5e, 0xed, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x0043ED9C..0x0043ED9F
// padding 0043ed9c..0043ed9f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001490")
extern "C" unsigned char text_padding_0043ed9c[] = {
    0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()

// data: 0x0043EDFC..0x0043EE23
// data 0043edfc..0043ee23: ["text_range_map:defined_data", "full+augmented listing typed data"]
#pragma data_seg(".d001491")
extern "C" unsigned char text_data_0043edfc[] = {
    0xc6, 0xed, 0x43, 0x00, 0xcf, 0xed, 0x43, 0x00, 0xd8, 0xed, 0x43, 0x00, 0xe1, 0xed, 0x43, 0x00,
    0xf9, 0xed, 0x43, 0x00, 0xf9, 0xed, 0x43, 0x00, 0xf9, 0xed, 0x43, 0x00, 0xf9, 0xed, 0x43, 0x00,
    0xea, 0xed, 0x43, 0x00, 0xf3, 0xed, 0x43, 0x00,
};
#pragma data_seg()

// padding: 0x0043EE24..0x0043EE2F
// padding 0043ee24..0043ee2f: ["text_range_map candidate_pattern=repeated_CC/00 or inspected INT3 run"]
#pragma data_seg(".d001492")
extern "C" unsigned char text_padding_0043ee24[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()
