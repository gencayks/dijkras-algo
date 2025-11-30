from manim import *

class FirstScene(Scene):
    def construct(self):
        # Create a Square
        sq = Square(color=BLUE, fill_opacity=0.5)
        sq.scale(2)

        # Create Text
        text = Text("RTX 4080 Online", font_size=48)

        # Animation
        self.play(DrawBorderThenFill(sq), run_time=1.5)
        self.play(Rotate(sq, PI/4))
        self.play(ReplacementTransform(sq, text))
        self.wait(1)

