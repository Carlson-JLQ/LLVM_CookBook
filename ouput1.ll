; ModuleID = 'testFile.ll'
source_filename = "testFile.ll"

define i32 @test1(i32 %A) {
  ret i32 %A
}

define internal i32 @test(i32 %x, i32 %dead) {
  ret i32 %x
}

define i32 @caller() {
  %A = call i32 @test(i32 123, i32 456)
  ret i32 %A
}
