class Sdl2Ttf < Formula
  desc "Library for using TrueType fonts in SDL applications"
  homepage "https://github.com/libsdl-org/SDL_ttf"
  url "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.tar.gz"
  sha256 "9dc71ed93487521b107a2c4a9ca6bf43fb62f6bddd5c26b055e6b91418a22053"
  license "Zlib"

  head do
    url "https://github.com/libsdl-org/SDL_ttf.git", branch: "main"

    depends_on "autoconf" => :build
    depends_on "automake" => :build
    depends_on "libtool" => :build
  end

  depends_on "pkg-config" => :build
  depends_on "freetype"
  depends_on "harfbuzz"
  depends_on "sdl2"

  def install
    inreplace "SDL2_ttf.pc.in", "@prefix@", HOMEBREW_PREFIX

    system "./autogen.sh" if build.head?

    # `--enable-harfbuzz` is the default, but we pass it
    # explicitly to generate an error when it isn't found.
    system "./configure", "--disable-freetype-builtin",
                          "--disable-harfbuzz-builtin",
                          "--enable-harfbuzz",
                          *std_configure_args
    system "make", "install"
  end

  test do
    (testpath/"test.c").write <<~EOS
      #include <SDL2/SDL_ttf.h>

      int main()
      {
          int success = TTF_Init();
          TTF_Quit();
          return success;
      }
    EOS
    system ENV.cc, "test.c", "-I#{Formula["sdl2"].opt_include}/SDL2", "-L#{lib}", "-lSDL2_ttf", "-o", "test"
    system "./test"
  end
end
