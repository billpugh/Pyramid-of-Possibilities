




public enum AnimationProgram {

    e_Mute(Animation.TweakKind.UNSIGNED),

    // Animations defined by Bill Pugh (WWP)
    e_ChangingColor,
    e_CircularGradient,
    e_ColorWorms(Animation.TweakKind.UNSIGNED),
    e_Chasers,
    e_FlashAttack(Animation.TweakKind.CYCLIC),
    e_Snow(Animation.TweakKind.CYCLIC),
    e_Swirl,
    e_GlowFade,
    e_LiftOff,
    e_Beacon,
    e_WWPAnimationTest,
    e_ActivityLevelAnimation,
    e_SideEffects (Animation.TweakKind.CYCLIC_UNARY),

    // Danny's animations.
    e_Qbert,   // RGB simple
    e_DRAnimation1,   // RNBeam
    e_FlashEcho,
    e_Radial,

    // Antoine's animations
    e_Flashes,
    e_MovingFaces,
    e_Explosion,

    // Branden's animations
    e_Kittens,

    // meelows animations
    e_MMAnimation1;         // strip color cycles through HSV, tapping activity brightens, no activity fades out
    
    
    
    final public Animation.TweakKind tweakKind;
    private AnimationProgram(Animation.TweakKind tweakKind) {
        this.tweakKind = tweakKind;
    }
    private AnimationProgram() {
        this(Animation.TweakKind.SIGNED);
    }
    static final int SIZE = values().length;
    
    

}
