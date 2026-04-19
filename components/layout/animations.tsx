"use client"

import { ReactNode } from "react"
import { motion, useScroll, useSpring } from "framer-motion"
import { forwardRef } from "react"

export const ScrollProgress = () => {
  const { scrollYProgress } = useScroll()
  const scaleX = useSpring(scrollYProgress, {
    stiffness: 100,
    damping: 30,
    restDelta: 0.001
  })

  return (
    <motion.div
      className="fixed top-0 left-0 right-0 h-1 bg-primary z-50 origin-left"
      style={{ scaleX }}
    />
  )
}

export const RevealOnScroll = ({ children, animation = "slideUp", duration = 0.6 }: { children: ReactNode, animation?: "slideUp" | "slideDown" | "slideLeft" | "slideRight" | "zoomIn" | "fadeIn", duration?: number }) => {
  const variants = {
    slideUp: { hidden: { opacity: 0, y: 50 }, visible: { opacity: 1, y: 0 } },
    slideDown: { hidden: { opacity: 0, y: -50 }, visible: { opacity: 1, y: 0 } },
    slideLeft: { hidden: { opacity: 0, x: 50 }, visible: { opacity: 1, x: 0 } },
    slideRight: { hidden: { opacity: 0, x: -50 }, visible: { opacity: 1, x: 0 } },
    zoomIn: { hidden: { opacity: 0, scale: 0.8 }, visible: { opacity: 1, scale: 1 } },
    fadeIn: { hidden: { opacity: 0 }, visible: { opacity: 1 } }
  }

  return (
    <motion.div
      initial="hidden"
      whileInView="visible"
      viewport={{ once: true, margin: "-100px" }}
      transition={{ duration, ease: [0.22, 1, 0.36, 1] }}
      variants={variants[animation]}
    >
      {children}
    </motion.div>
  )
}

export const StaggerContainer = ({ children, className = "", staggerDelay = 0.1 }: { children: ReactNode, className?: string, staggerDelay?: number }) => {
  return (
    <motion.div
      initial="hidden"
      whileInView="visible"
      viewport={{ once: true, margin: "-100px" }}
      variants={{
        hidden: {},
        visible: { transition: { staggerChildren: staggerDelay } }
      }}
      className={className}
    >
      {children}
    </motion.div>
  )
}

export const StaggerItem = ({ children, animation = "slideUp" }: { children: ReactNode, animation?: "slideUp" | "slideDown" | "slideLeft" | "slideRight" | "zoomIn" | "fadeIn" }) => {
  const variants = {
    slideUp: { hidden: { opacity: 0, y: 40 }, visible: { opacity: 1, y: 0 } },
    slideDown: { hidden: { opacity: 0, y: -40 }, visible: { opacity: 1, y: 0 } },
    slideLeft: { hidden: { opacity: 0, x: 40 }, visible: { opacity: 1, x: 0 } },
    slideRight: { hidden: { opacity: 0, x: -40 }, visible: { opacity: 1, x: 0 } },
    zoomIn: { hidden: { opacity: 0, scale: 0.9 }, visible: { opacity: 1, scale: 1 } },
    fadeIn: { hidden: { opacity: 0 }, visible: { opacity: 1 } }
  }

  return (
    <motion.div variants={variants[animation]} transition={{ duration: 0.5, ease: [0.22, 1, 0.36, 1] }}>
      {children}
    </motion.div>
  )
}

export const SectionWrapper = forwardRef<HTMLDivElement, { children: ReactNode, className?: string, orbs?: boolean, orbTheme?: "primary" | "secondary" | "mixed", parallaxIntensity?: number }>(
  ({ children, className = "", orbs = false, orbTheme = "primary", parallaxIntensity = 10 }, ref) => {
    return (
      <div ref={ref} className={`relative ${className}`}>
        {orbs && (
          <div className="absolute inset-0 overflow-hidden pointer-events-none z-0 flex items-center justify-center">
            <div className={`w-[40rem] h-[40rem] opacity-20 rounded-full blur-3xl animate-pulse ${orbTheme === "mixed" ? "bg-gradient-to-r from-primary to-secondary" : orbTheme === "secondary" ? "bg-secondary" : "bg-primary"}`} />
          </div>
        )}
        <div className="relative z-10 w-full h-full">
            {children}
        </div>
      </div>
    )
  }
)
SectionWrapper.displayName = "SectionWrapper"
