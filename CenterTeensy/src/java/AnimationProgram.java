
public enum AnimationProgram {

	 e_LiftOff,
	    e_Beacon,
	    // Branden's animations
	    e_Kittens,

	    e_FlashEcho,

	    e_Radial,
	    e_Mute,


	    e_GlowFade,

	    e_WWPAnimationTest,
	    e_ActivityLevelAnimation,

	    e_SideEffects,

	    // Animations defined by Bill Pugh (WWP)
	    e_ChangingColor,
	    e_CircularGradient,

	    e_ColorWorms,
	    e_Chasers,
	    e_FlashAttack,
	    e_Snow,
	    e_Swirl,

	    // Danny's animations.
	    e_Qbert,   // RGB simple
	    e_DRAnimation1,   // RNBeam

	    // Antoine's animations
	    e_Flashes,
	    e_MovingFaces,
	    e_Explosion;

    
    
    
    final public Animation.TweakKind tweakKind;
    private AnimationProgram(Animation.TweakKind tweakKind) {
        this.tweakKind = tweakKind;
    }
    private AnimationProgram() {
        this(Animation.TweakKind.SIGNED);
    }
    static final int SIZE = values().length;
    
    

}
